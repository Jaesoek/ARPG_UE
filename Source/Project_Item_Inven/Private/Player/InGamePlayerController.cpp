// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/InGamePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"

#include "Player/TpsCharacter.h"

#include "UI/InGameHUD.h"
#include "UI/InventoryUI.h"
#include "UI/SkillSlot.h"

#include "Skill/BaseSkillComponent.h"

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("KeyEsc", IE_Pressed, this, &AInGamePlayerController::KeyESC);
	InputComponent->BindAction("KeyAlt", IE_Pressed, this, &AInGamePlayerController::KeyAlt_Pressed);
	InputComponent->BindAction("KeyAlt", IE_Released, this, &AInGamePlayerController::KeyAlt_Released);

	InputComponent->BindAction("Inventory", IE_Pressed, this, &AInGamePlayerController::Inventory);
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly{});
}

void AInGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	m_TpsCharacter = Cast<ATpsCharacter>(InPawn);

	// UI Setting
	if (Inventory_UI)
	{
		m_ptrInventory = Cast<UInventoryUI>(CreateWidget(GetWorld(), Inventory_UI));
		m_ptrInventory->AddToViewport();
		m_ptrInventory->SetVisibility(ESlateVisibility::Hidden);
	}
	if (InGameHUD_UI)
	{
		m_ptrInGameHUD = Cast<UInGameHUD>(CreateWidget(GetWorld(), InGameHUD_UI));
		m_ptrInGameHUD->AddToViewport();
	}
}

void AInGamePlayerController::KeyESC()
{
	// Inventory 열려있으면 제거
	if (IsValid(m_ptrInventory) && m_ptrInventory->GetVisibility() != ESlateVisibility::Hidden)
	{
		m_ptrInventory->SetVisibility(ESlateVisibility::Hidden);
		SetShowMouseCursor(false);
		SetInputMode(FInputModeGameOnly{});
	}
}

void AInGamePlayerController::KeyAlt_Pressed()
{
	SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI{});
}

void AInGamePlayerController::KeyAlt_Released()
{
	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly{});
}

void AInGamePlayerController::Inventory()
{
	if (IsValid(m_ptrInventory) && m_ptrInventory->GetVisibility() != ESlateVisibility::Hidden)
	{
		m_ptrInventory->SetVisibility(ESlateVisibility::Hidden);
		SetShowMouseCursor(false);
		SetInputMode(FInputModeGameOnly{});
	}
	else
	{
		m_ptrInventory->SetVisibility(ESlateVisibility::Visible);
		SetShowMouseCursor(true);
		SetInputMode(FInputModeGameAndUI{});
	}
}