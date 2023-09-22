// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuController.generated.h"


class UMainMenuHUD;
class UOptionHUD;

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	TSubclassOf<UMainMenuHUD> m_HUD_MainMenu;

	UMainMenuHUD* m_ptrMainmenuHUD;

	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	TSubclassOf<UOptionHUD> m_HUD_Option;

	UOptionHUD* m_ptrOptionHUD;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	bool OpenMainMenu();
	UFUNCTION()
	bool OpenOptions();
};
