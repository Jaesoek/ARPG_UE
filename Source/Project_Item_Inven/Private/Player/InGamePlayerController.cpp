// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/InGamePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Player/TpsCharacter.h"

#include "UI/InGameHUD.h"
#include "UI/InventoryUI.h"
#include "UI/SkillSlot.h"

#include "Skill/BaseSkillComponent.h"

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Inventory", IE_Pressed, this, &AInGamePlayerController::Inventory);
	InputComponent->BindAction("Interaction", IE_Pressed, this, &AInGamePlayerController::Interaction);
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Inventory 셋팅
	if (Inventory_UI)
	{
		m_ptrInventory = Cast<UUserWidget>(	CreateWidget(GetWorld(), Inventory_UI));
		m_ptrInventory->AddToViewport();
	}

	if (InGameHUD_UI)
	{
		m_ptrInGameHUD = Cast<UInGameHUD>(CreateWidget(GetWorld(), InGameHUD_UI));
		m_ptrInGameHUD->AddToViewport();
	}
}

void AInGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	m_TpsCharacter = Cast<ATpsCharacter>(InPawn);

	// TODO: Character가 들고 있는 SkillComponent / UI_InGame SkillSlot 간에 바인딩 진행
}

void AInGamePlayerController::Inventory()
{
	if (m_ptrInventory)
	{
		UWidget* inventory = m_ptrInventory->GetWidgetFromName(TEXT("InventoryMenu"));
		switch (inventory->Visibility)
		{
		case ESlateVisibility::Hidden:
			inventory->SetVisibility(ESlateVisibility::Visible);
			SetShowMouseCursor(true);
			SetInputMode(FInputModeGameAndUI{});
			break;
		default:
			inventory->SetVisibility(ESlateVisibility::Hidden);
			SetShowMouseCursor(false);
			SetInputMode(FInputModeGameOnly{});
			break;
		}
	}
}

void AInGamePlayerController::Interaction()
{
	
}
