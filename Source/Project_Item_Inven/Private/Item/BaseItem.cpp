// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseItem.h"
#include "Curve.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "InGamePlayerState.h"
#include "Player/Project_Item_InvenCharacter.h"


ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = true;

	m_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	m_MeshComponent->AttachTo(RootComponent);

	// Base Collision Setting
	m_MeshComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
	m_MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	m_MeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	m_MeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	m_CurveSizeFloat = CreateDefaultSubobject<UCurveFloat>(TEXT("DropSizeCurve"));
	m_uMaxDropRadius = 200;
}

void ABaseItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	float scaleValue = m_CurveSizeFloat->GetFloatValue(0.f);
	SetActorScale3D(FVector(scaleValue));

	m_MeshComponent->SetSimulatePhysics(true);
	m_MeshComponent->SetNotifyRigidBodyCollision(true);
	m_MeshComponent->SetGenerateOverlapEvents(true);
	m_MeshComponent->OnComponentHit.AddDynamic(this, &ABaseItem::OnHit);
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	// 생성시 Dropping state로 초기화
	setStatus(EItemStatus::Dropping);
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (m_eItemStatus)
	{
		case EItemStatus::Dropping:
		{
			if (m_CurveSizeFloat)
			{
				m_fDropTime += DeltaTime;

				// Size(with Curve), Rotation
				float scaleValue = m_CurveSizeFloat->GetFloatValue(m_fDropTime);
				SetActorScale3D(FVector(scaleValue));
				SetActorRelativeRotation(FRotator(m_fDropTime * 360 * 2, 0.f, 0.f));

				// Location
				auto&& location = FMath::Lerp(m_StartPosition, m_DropPosition, m_fDropTime / 2.f);
				location.Z += sinf(m_fDropTime * PI) * 200.f;
				SetActorLocation(location);
			}
			break;
		}
		case EItemStatus::Dropped:
		{
			break;
		}
	}
}

void ABaseItem::setStatus(EItemStatus eStatus)
{
	m_eItemStatus = eStatus;

	if (m_eItemStatus == EItemStatus::Dropped)
	{
		SetActorRelativeRotation(FRotator::ZeroRotator);

		m_MeshComponent->SetSimulatePhysics(false);
		m_MeshComponent->SetNotifyRigidBodyCollision(false);
		m_MeshComponent->SetGenerateOverlapEvents(true);
	}
	else if (m_eItemStatus == EItemStatus::Dropping)
	{
		m_fDropTime = 0.f;
		float nRadius = FMath::RandRange(50, m_uMaxDropRadius);
		float fAngle = (float)FMath::RandRange(0, 359);
		m_StartPosition = GetActorLocation();
		m_DropPosition = FVector(cos(fAngle), sinf(fAngle), 0.f) * nRadius + m_StartPosition;

		m_MeshComponent->SetSimulatePhysics(true);
		m_MeshComponent->SetNotifyRigidBodyCollision(true);
		m_MeshComponent->SetGenerateOverlapEvents(false);
	}
}

void ABaseItem::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	setStatus(EItemStatus::Dropped);
}

void ABaseItem::SetFocused(bool isFocused)
{
	m_MeshComponent->SetRenderCustomDepth(isFocused);
}

void ABaseItem::Interact(const AProject_Item_InvenCharacter* character)
{
	AInGamePlayerState* playerState = Cast<AInGamePlayerState>(character->GetPlayerState());
	bool successAddItem = playerState->addItem(
		GetClass(),
		m_TextItemName,
		m_TextItemDescription,
		m_Thumbnail
	);
	if (successAddItem)
	{
		// 습득 FX 생성
		FTransform actorTransform = GetActorTransform();
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			m_EffectInteraction,
			actorTransform
		);

		Destroy();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Inventory Full!!"));
	}
}
