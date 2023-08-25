
#include "Item/EquipItem.h"
#include "Skill/BaseSkillComponent.h"

AEquipItem::AEquipItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEquipItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEquipItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

