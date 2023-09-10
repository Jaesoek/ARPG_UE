// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITEM_INVEN_API UMainMenuHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UMenuSelectUI* SelectNewGame;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UMenuSelectUI* SelectLoadGame;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UMenuSelectUI* SelectOption;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UMenuSelectUI* SelectQuit;

private:
	virtual void NativeOnInitialized() override;

private:
	void StartNewGame();
	void OpenOptionWidget();
	void Quit();
};
