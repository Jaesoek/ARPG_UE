// Fill out your copyright notice in the Description page of Project Settings.


#include "InstanceARPG.h"
#include "SaveOptions.h"

#include "Kismet/GameplayStatics.h"

FString UInstanceARPG::SaveOptionSlotName = TEXT("Options");

void UInstanceARPG::InitOptions()
{
	auto option = GetOptions();
	MasterVolumeChange(option->MasterVolume);
	MusicVolumeChange(option->MusicVolume);
	EffectVolumeChange(option->EffectVolume);
}

void UInstanceARPG::MasterVolumeChange(float fVolume)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), m_MasterMix, m_MasterClass, FMath::Clamp<float>(fVolume, 0.f, 1.f));
}

void UInstanceARPG::MusicVolumeChange(float fVolume)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), m_MusicMix, m_MusicClass, FMath::Clamp<float>(fVolume, 0.f, 1.f));
}

void UInstanceARPG::EffectVolumeChange(float fVolume)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), m_EffectMix, m_EffectClass, FMath::Clamp<float>(fVolume, 0.f, 1.f));
}

USaveOptions* UInstanceARPG::GetOptions()
{
	auto savedOptions = Cast<USaveOptions>(UGameplayStatics::LoadGameFromSlot(SaveOptionSlotName, 0));
	if (savedOptions == nullptr)
	{
		savedOptions = GetMutableDefault<USaveOptions>();
	}
	return savedOptions;
}

bool UInstanceARPG::SaveOptions(float masterVolume, float musicVolume, float effectVolume)
{
	auto ptrSavedOptions = NewObject<USaveOptions>();
	ptrSavedOptions->MasterVolume = masterVolume;
	ptrSavedOptions->MusicVolume = musicVolume;
	ptrSavedOptions->EffectVolume = effectVolume;

	if (!UGameplayStatics::SaveGameToSlot(ptrSavedOptions, SaveOptionSlotName, 0))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Save Option Error"));
		return false;
	}
	return true;
}
