// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Item_Inven.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentSlot.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API UEquipmentSlot : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = true))
	UTexture2D* m_ptrTexture;

	UPROPERTY(BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = true))
	EEquipType m_eEquipType;

public:
	FORCEINLINE void setTexture(UTexture2D* texture) { m_ptrTexture = texture; };
	FORCEINLINE const UTexture2D* getTexture() const { return m_ptrTexture; };

	FORCEINLINE void setEquipType(EEquipType equipType) { m_eEquipType = equipType; };
	FORCEINLINE const EEquipType getEquipType() const { return m_eEquipType; };
};
