// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SkillSlot.h"
#include "Components/ProgressBar.h"

void USkillSlot::UpdateCoolTimePercent(float fPercent)
{
	m_ProgressCoolTime->SetPercent(fPercent);
}
