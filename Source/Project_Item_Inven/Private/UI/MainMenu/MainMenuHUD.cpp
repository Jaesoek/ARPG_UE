// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/MainMenuHUD.h"
#include "UI/MainMenu/MenuSelectUI.h"

#include "Components/TextBlock.h"

#include "Kismet/KismetSystemLibrary.h"

void UMainMenuHUD::NativeOnInitialized()
{
	OnInitialized();

	SelectNewGame->TextBlock_Select->SetText(FText::FromString("New Game"));
	SelectLoadGame->TextBlock_Select->SetText(FText::FromString("Load Game"));
	SelectOption->TextBlock_Select->SetText(FText::FromString("Option"));
	SelectQuit->TextBlock_Select->SetText(FText::FromString("Quit"));
}

void UMainMenuHUD::StartNewGame()
{

}

void UMainMenuHUD::OpenOptionWidget()
{
}

void UMainMenuHUD::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}


