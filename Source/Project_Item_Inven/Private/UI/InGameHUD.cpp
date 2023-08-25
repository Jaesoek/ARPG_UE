// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"
#include "UI/SkillSlot.h"
#include "Components/ProgressBar.h"

void UInGameHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Tick(MyGeometry, InDeltaTime);

}
