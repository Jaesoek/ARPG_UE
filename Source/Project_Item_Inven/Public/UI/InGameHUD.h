// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUD.generated.h"


class USkillSlot;

/**
 * 
 */
UCLASS()
class PROJECT_ITEM_INVEN_API UInGameHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	// Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* border_profile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* img_profile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* progress_hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* progress_sp;

	// Init in blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillList)
	TArray<USkillSlot*> m_arrSkillSlot;


	// Animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Animation_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Animation_Heal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Animation_Heal_Progress;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
};
