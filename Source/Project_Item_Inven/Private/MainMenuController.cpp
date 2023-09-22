// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuController.h"
#include "InstanceARPG.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "UI/MainMenu/MainMenuHUD.h"
#include "UI/MainMenu/OptionHUD.h"

#include "Kismet/GameplayStatics.h"

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();

	auto ptrGameInstance = Cast<UInstanceARPG>(GetGameInstance());
	ptrGameInstance->InitOptions();

	SetShowMouseCursor(true);
	SetInputMode(FInputModeUIOnly{});

	if (m_HUD_MainMenu)
		m_ptrMainmenuHUD = Cast<UMainMenuHUD>(CreateWidget(GetWorld(), m_HUD_MainMenu));
	if (m_HUD_Option)
		m_ptrOptionHUD = Cast<UOptionHUD>(CreateWidget(GetWorld(), m_HUD_Option));

	m_ptrMainmenuHUD->AddToViewport();
}

bool AMainMenuController::OpenMainMenu()
{
	if (m_ptrMainmenuHUD->IsInViewport())
		return false;

	if (m_ptrOptionHUD->IsInViewport())
		m_ptrOptionHUD->RemoveFromViewport();
	m_ptrMainmenuHUD->AddToViewport();
	return true;
}

bool AMainMenuController::OpenOptions()
{
	if (m_ptrOptionHUD->IsInViewport())
		return false;

	if (m_ptrMainmenuHUD->IsInViewport())
		m_ptrMainmenuHUD->RemoveFromViewport();
	m_ptrOptionHUD->AddToViewport();
	return true;
}


