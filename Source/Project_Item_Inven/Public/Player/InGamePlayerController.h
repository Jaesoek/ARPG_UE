// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

class UInGameHUD;

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	class ATpsCharacter* m_TpsCharacter;

private: // UI 설정
	// InGamePlay Mode 에서 HUD 출력
	UPROPERTY(EditAnywhere, Category = UserInterface)
	TSubclassOf<UInGameHUD> InGameHUD_UI;

	UPROPERTY(EditAnywhere, Category = UserInterface)
	TSubclassOf<UUserWidget> Inventory_UI;

	UInGameHUD* m_ptrInGameHUD;
	UUserWidget* m_ptrInventory;

public:
	/* Bind to key event "Inventory" */
	void Inventory();

	/* Bind to key event "Interaction" */
	void Interaction();
};
