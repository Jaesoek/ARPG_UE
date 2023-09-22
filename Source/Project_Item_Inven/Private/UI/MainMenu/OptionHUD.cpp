// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/OptionHUD.h"
#include "MainMenuController.h"
#include "SaveOptions.h"
#include "InstanceARPG.h"

#include "Components/Slider.h"
#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"

void UOptionHUD::NativeOnInitialized()
{
	OnInitialized();

	m_ownerController = GetOwningPlayer<AMainMenuController>();
	m_ptrGameInstance = Cast<UInstanceARPG>(GetGameInstance());

	dMaster.BindUFunction(this, "MasterVolumeChange");
	dMusic.BindUFunction(this, "MusicVolumeChange");
	dEffect.BindUFunction(this, "EffectVolumeChange");

	dExit.BindUFunction(this, "ExitOption");

	Slider_MasterVolume->OnValueChanged.Add(dMaster);
	Slider_MusicVolume->OnValueChanged.Add(dMusic);
	Slider_EffectVolume->OnValueChanged.Add(dEffect);

	Button_Exit->OnClicked.Add(dExit);
}

void UOptionHUD::NativeConstruct()
{
	auto savedOptions = m_ptrGameInstance->GetOptions();

	Slider_MasterVolume->SetValue(savedOptions->MasterVolume);
	Slider_MusicVolume->SetValue(savedOptions->MusicVolume);
	Slider_EffectVolume->SetValue(savedOptions->EffectVolume);
}

void UOptionHUD::MasterVolumeChange(float fVolume)
{
	m_ptrGameInstance->MasterVolumeChange(fVolume);
}

void UOptionHUD::MusicVolumeChange(float fVolume)
{
	m_ptrGameInstance->MusicVolumeChange(fVolume);
}

void UOptionHUD::EffectVolumeChange(float fVolume)
{
	m_ptrGameInstance->EffectVolumeChange(fVolume);
}

void UOptionHUD::ExitOption()
{
	bool result = m_ptrGameInstance->SaveOptions(
		Slider_MasterVolume->GetValue(), Slider_MusicVolume->GetValue(), Slider_EffectVolume->GetValue()
	);

	if (m_ownerController)
		m_ownerController->OpenMainMenu();
}

