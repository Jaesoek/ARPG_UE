// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseItem.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

#include "InGamePlayerState.h"
#include "Player/TpsCharacter.h"


ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = true;

	m_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	m_MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_MeshComponent->bReceivesDecals = false;

	/*
	// Base Collision Setting
	m_MeshComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
	m_MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	m_MeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	m_MeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	*/
}

void ABaseItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	m_MeshComponent->SetSimulatePhysics(false);
	m_MeshComponent->SetNotifyRigidBodyCollision(false);
	m_MeshComponent->SetGenerateOverlapEvents(true);
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	check(m_eItemType != EItemType::None);
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseItem::SetFocused(bool isFocused)
{
	m_MeshComponent->SetRenderCustomDepth(isFocused);
}

bool ABaseItem::Interact(const ACharacter* character, FString& strUnableReason)
{
	AInGamePlayerState* playerState = Cast<AInGamePlayerState>(character->GetPlayerState());
	bool successAddItem = playerState->addItem(GetClass());

	if (successAddItem)
	{
		FTransform actorTransform = GetActorTransform();
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			m_EffectInteraction,
			actorTransform
		);

		Destroy();

		return true;
	}

	strUnableReason += TEXT("Inventory Full!!");
	return false;
}

bool ABaseItem::UseItem(ACharacter* character)
{
	check(0 && "You must override this");
	return false;
}

bool ABaseItem::UseItemBP(ACharacter* character)
{
	return UseItem(character);
}
