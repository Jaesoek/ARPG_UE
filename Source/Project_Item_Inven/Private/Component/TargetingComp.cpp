

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
	TargetingSphere->InitSphereRadius(120.f);

	// Set Targeting
	TargetingSphere->SetCollisionObjectType(ECC_Pawn);
	TargetingSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TargetingSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	TargetingSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TargetingSphere->SetGenerateOverlapEvents(true);

	TargetingSphere->OnComponentBeginOverlap.AddDynamic(this, &UTargetingComp::OnTargetingOverlap);
	TargetingSphere->OnComponentEndOverlap.AddDynamic(this, &UTargetingComp::EndTargetingOverlap);
}

void UTargetingComp::BeginPlay()
{
	Super::BeginPlay();

	m_OwnerChar = Cast<ACharacter>(GetAttachmentRootActor());
}


void UTargetingComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_bFocused)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Targeting work"));
	}
	else if (m_bFocused && m_OwnerChar != nullptr && IsValid(m_TargetActor))
	{

		FRotator&& rotation = UKismetMathLibrary::FindLookAtRotation(
			m_OwnerChar->GetActorLocation(), m_TargetActor->GetActorLocation()
		);

		FRotator&& finalRotation = UKismetMathLibrary::RInterpTo(m_OwnerChar->GetActorRotation(), rotation, DeltaTime, 5.f);
		m_OwnerChar->GetController()->SetControlRotation(finalRotation);
	}

}

void UTargetingComp::OnTargetingOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	m_TargetActor = OtherActor;
}

void UTargetingComp::EndTargetingOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	m_TargetActor = nullptr;
}

