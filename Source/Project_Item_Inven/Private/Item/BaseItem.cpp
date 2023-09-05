// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseItem.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

#include "InGamePlayerState.h"
#include "Player/Project_Item_InvenCharacter.h"

#include "Item/Components/ItemDropComponent.h"


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

	m_ItemDropComponent = NewObject<UItemDropComponent>(this, TEXT("ItemDropComp"));
//	m_ItemDropComponent->RegisterComponent();
//	AddInstanceComponent(m_ItemDropComponent);
}

void ABaseItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	m_MeshComponent->SetSimulatePhysics(true);
	m_MeshComponent->SetNotifyRigidBodyCollision(true);
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


void ABaseItem::UseItem_Implementation()
{

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
		// ½Àµæ FX »ý¼º
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
