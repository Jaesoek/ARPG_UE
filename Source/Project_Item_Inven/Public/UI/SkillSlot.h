// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITEM_INVEN_API USkillSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UProgressBar* m_ProgressCoolTime;

public:
	void UpdateCoolTimePercent(float fPercent);
	void SetSlotIcon(UTexture2D* thumbnail);
};
