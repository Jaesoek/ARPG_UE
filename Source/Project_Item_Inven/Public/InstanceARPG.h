// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "InstanceARPG.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API UInstanceARPG : public UGameInstance
{
	GENERATED_BODY()

public:
	static FString SaveOptionSlotName;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundClass* m_MasterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundClass* m_MusicClass;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundClass* m_EffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundMix* m_MasterMix;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundMix* m_MusicMix;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundMix* m_EffectMix;

public:
	void InitOptions();

public:
	UFUNCTION(BlueprintCallable)
	void MasterVolumeChange(float fVolume);

	UFUNCTION(BlueprintCallable)
	void MusicVolumeChange(float fVolume);

	UFUNCTION(BlueprintCallable)
	void EffectVolumeChange(float fVolume);

	class USaveOptions* GetOptions();

	bool SaveOptions(float masterVolume, float musicVolume, float effectVolume);
};
