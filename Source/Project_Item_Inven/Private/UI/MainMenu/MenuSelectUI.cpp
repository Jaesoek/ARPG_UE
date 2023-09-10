// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/MenuSelectUI.h"

void UMenuSelectUI::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	PlayAnimation(Anim_Focused);
}

void UMenuSelectUI::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	PlayAnimation(Anim_Focused, 0.0f, 1, EUMGSequencePlayMode::Reverse);
}

FReply UMenuSelectUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto& replayResult = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return replayResult;
}

