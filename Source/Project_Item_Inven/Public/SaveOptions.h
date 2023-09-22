// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveOptions.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITEM_INVEN_API USaveOptions : public USaveGame
{
	GENERATED_BODY()

public:
	USaveOptions();

	UPROPERTY()
	float MasterVolume;
	
	UPROPERTY()
	float MusicVolume;
	
	UPROPERTY()
	float EffectVolume;
};
