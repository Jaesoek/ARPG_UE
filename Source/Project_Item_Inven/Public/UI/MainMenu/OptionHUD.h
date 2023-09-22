// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API UOptionHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	static FString SaveOptionSlotName;

private:
	class AMainMenuController* m_ownerController;
	class UInstanceARPG* m_ptrGameInstance;

public:
	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	class USlider* Slider_MasterVolume;
	
	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	class USlider* Slider_MusicVolume;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	class USlider* Slider_EffectVolume;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	class UButton* Button_Exit;

private:
	FScriptDelegate dMaster;
	FScriptDelegate dMusic;
	FScriptDelegate dEffect;

	FScriptDelegate dExit;

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void MusicVolumeChange(float fVolume);

	UFUNCTION()
	void MasterVolumeChange(float fVolume);

	UFUNCTION()
	void EffectVolumeChange(float fVolume);

	UFUNCTION()
	void ExitOption();
};
