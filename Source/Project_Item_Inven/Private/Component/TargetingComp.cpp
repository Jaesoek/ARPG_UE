

#include "Component/TargetingComp.h"
#include "GameFramework/Character.h"

#include "Components/SphereComponent.h"

#include "Kismet/KismetMathLibrary.h"

UTargetingComp::UTargetingComp()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Targeting Setting
	TargetingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TargetingSphere"));
	TargetingSphere->SetupAttachment(this);
	TargetingSphere->InitSphereRadius(2000.f);

	// Set Targeting
	TargetingSphere->SetCollisionObjectType(ECC_Pawn);
	TargetingSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TargetingSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	TargetingSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TargetingSphere->SetGenerateOverlapEvents(true);

	TargetingSphere->OnComponentBeginOverlap.AddDynamic(this, &UTargetingComp::OnTargetingOverlap);
	TargetingSphere->OnComponentEndOverlap.AddDynamic(this, &UTargetingComp::EndTargetingOverlap);

	// Init owner character
	m_OwnerChar = Cast<ACharacter>(GetAttachmentRootActor());

	// Init Data List
	m_TargetMark = nullptr;
}

void UTargetingComp::BeginPlay()
{
	Super::BeginPlay();
}


void UTargetingComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(m_TargetedActor))
	{
		FRotator&& targetRotation = UKismetMathLibrary::FindLookAtRotation(
			m_OwnerChar->GetActorLocation(), m_TargetedActor->GetActorLocation()
		);
		FRotator&& calculatedControlRotation = UKismetMathLibrary::RInterpTo(m_OwnerChar->GetControlRotation(), targetRotation, DeltaTime, 5.f);

		m_OwnerChar->GetController()->SetControlRotation(calculatedControlRotation);
	}
}

void UTargetingComp::OnTargetingOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_OwnerChar == OtherActor) return;

	m_setTargetActors.Emplace(OtherActor);
}

void UTargetingComp::EndTargetingOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	m_setTargetActors.Remove(OtherActor);
}

bool UTargetingComp::FocusTarget()
{
	// TODO: On / Off 기능으로 분리 필요
	if (m_setTargetActors.Num() <= 0 || m_TargetedActor != nullptr)
	{
		m_TargetedActor = nullptr;
		if (IsValid(m_TargetMark))
		{
			m_TargetMark->Destroy();
			m_TargetMark = nullptr;
		}
		return false;
	}

	// TODO: 리스트 내에서 선택로직 추가
	m_TargetedActor = *m_setTargetActors.begin();

	auto transform = m_TargetedActor->GetTransform();
	m_TargetMark = GetWorld()->SpawnActor(m_class_TargetMark, &transform);

	FAttachmentTransformRules attachRule(EAttachmentRule::SnapToTarget, true);
	m_TargetMark->AttachToActor(m_TargetedActor, attachRule, FName(TEXT("socket_targeting")));

	return true;
}

void UTargetingComp::SwitchFocusedTarget()
{
	if (m_setTargetActors.Num() == 0) return;

	auto iterator = m_setTargetActors.begin();
	while (iterator != m_setTargetActors.end() && m_setTargetActors[iterator.GetId()] != m_TargetedActor)
	{
		++iterator;
	}

	if (iterator == m_setTargetActors.end())
		m_TargetedActor = m_setTargetActors[m_setTargetActors.begin().GetId()];
	else
		m_TargetedActor = m_setTargetActors[iterator.GetId()];
}
