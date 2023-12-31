// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/MainMenuHUD.h"
#include "UI/MainMenu/MenuSelectUI.h"
#include "MainMenuController.h"

#include "Components/TextBlock.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


void UMainMenuHUD::NativeOnInitialized()
{
	OnInitialized();

	m_ownerController = GetOwningPlayer<AMainMenuController>();

	SelectNewGame->TextBlock_Select->SetText(FText::FromString("New Game"));
	SelectLoadGame->TextBlock_Select->SetText(FText::FromString("Load Game"));
	SelectOption->TextBlock_Select->SetText(FText::FromString("Option"));
	SelectQuit->TextBlock_Select->SetText(FText::FromString("Quit"));

	SelectNewGame->OnBtnPressed.BindUObject(this, &UMainMenuHUD::StartNewGame);
	SelectOption->OnBtnPressed.BindUObject(this, &UMainMenuHUD::OpenOptionWidget);
	SelectQuit->OnBtnPressed.BindUObject(this, &UMainMenuHUD::Quit);
}

void UMainMenuHUD::StartNewGame()
{
	if (!m_LevelToLoad.IsNull())
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), m_LevelToLoad);
	else
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("다음 레벨을 지정해주세요"));
}

void UMainMenuHUD::OpenOptionWidget()
{
	m_ownerController->OpenOptions();
}

void UMainMenuHUD::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}
