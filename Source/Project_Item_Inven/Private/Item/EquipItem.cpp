
#include "Item/EquipItem.h"

#include "Player/TpsCharacter.h"

#include "Skill/BaseSkillComponent.h"

AEquipItem::AEquipItem()
{
	PrimaryActorTick.bCanEverTick = true;

	m_eItemType = EItemType::Equipable;
}

bool AEquipItem::UseItem(ACharacter* character)
{
	auto tpsCharacter = Cast<ATpsCharacter>(character);
	return tpsCharacter->Equip(GetClass());
}
