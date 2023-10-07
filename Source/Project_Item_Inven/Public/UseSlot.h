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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void UseSlot();
};
