// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UseSlot.generated.h"

UINTERFACE(MinimalAPI)
class UUseSlot : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_ITEM_INVEN_API IUseSlot
{
	GENERATED_BODY()

public:
	virtual bool UseSlot_Pressed(FString& strUnableReason) = 0;
	virtual bool UseSlot_Released() = 0;
};
