// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Item_Inven.h"
#include "Item/BaseItem.h"
#include "EquipItem.generated.h"

UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API AEquipItem : public ABaseItem
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = ItemInfo, BlueprintReadOnly)
	EEquipType m_EquipType;

	UPROPERTY(EditDefaultsOnly, Category = ItemInfo, BlueprintReadOnly)
	EWeaponMode m_WeaponType;

	UPROPERTY(EditDefaultsOnly, Category = ItemInfo, BlueprintReadOnly)
	UAnimMontage* m_AttackMontage;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill List")
	TArray<TSubclassOf<class UBaseSkillComponent>> m_arrSkillComp;

public:	
	AEquipItem();

public:
	virtual bool UseItem(ACharacter* character) override;

	FORCEINLINE EEquipType GetEquipType() const { return m_EquipType; };
	FORCEINLINE EWeaponMode GetWeaponType() const { return m_WeaponType; };
	FORCEINLINE UAnimMontage* GetAttackMontage() const { return m_AttackMontage; };
};
