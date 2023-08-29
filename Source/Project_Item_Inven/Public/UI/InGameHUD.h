// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUD.generated.h"

class ATpsCharacter;
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
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* border_profile;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* img_profile;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* progress_hp;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* progress_sp;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* HorizontalBox_Skill;

	// Skill slots
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Skill_Slot_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Skill_Slot_2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Skill_Slot_3;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Skill_Slot_4;

	// Animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Animation_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Animation_Heal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Animation_Heal_Progress;

private:
	// TpsCharacter
	ATpsCharacter* m_pPlayerChar;

private:
	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void BindSkill();
};
