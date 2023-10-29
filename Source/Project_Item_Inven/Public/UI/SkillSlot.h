// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlot.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API USkillSlot : public UUserWidget
{
	GENERATED_BODY()

		friend class UInGameHUD;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UProgressBar* m_ProgressCoolTime;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Anim_CoolTime;

protected:
	UPROPERTY(BlueprintReadOnly)
	FKey m_bindedKey;

	UPROPERTY(BlueprintReadOnly)
	int m_nIndex;

	UPROPERTY(BlueprintReadOnly)
	UTexture2D* m_Thumbnail;

public:
	void UpdateCoolTimePercent(float fPercent);
	void SetSlotIcon(UTexture2D* thumbnail);

	FORCEINLINE void SetBindedKey(FKey key) { m_bindedKey = key; };
	FORCEINLINE FKey GetBindedKey() { return m_bindedKey; };
};
