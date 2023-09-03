// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

class UInGameHUD;
class UInventoryUI;

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
	TSubclassOf<UInventoryUI> Inventory_UI;

	UInGameHUD* m_ptrInGameHUD;
	UInventoryUI* m_ptrInventory;

private:
	/* Bind to key event "Inventory" */
	void KeyESC();

	/* Bind to key event "Inventory" */
	void Inventory();

public:
	FORCEINLINE UInGameHUD* GetInGameHUD() const { return m_ptrInGameHUD; };
};
