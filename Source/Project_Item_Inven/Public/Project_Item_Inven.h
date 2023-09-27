// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	None, Consumable, Equipable
};

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	Weapon, Helmet, Breast
};
