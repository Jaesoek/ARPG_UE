// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SkillSlot.h"
#include "Components/ProgressBar.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


void USkillSlot::UpdateCoolTimePercent(float fPercent)
{
	if (m_ProgressCoolTime->Percent > FLT_EPSILON && 1.f - fPercent <= FLT_EPSILON)
	{
		PlayAnimation(Anim_CoolTime);
	}
	m_ProgressCoolTime->SetPercent(1.f - fPercent);
}

void USkillSlot::SetSlotIcon(UTexture2D* thumbnail)
{
	m_Thumbnail = thumbnail;

	m_ProgressCoolTime->WidgetStyle.SetBackgroundImage(
		UWidgetBlueprintLibrary::MakeBrushFromTexture(thumbnail)
	);
}