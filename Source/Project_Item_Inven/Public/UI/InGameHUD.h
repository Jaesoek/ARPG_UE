// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUD.generated.h"

class ATpsCharacter;
class USkillSlot;
class UBuffCoolTimeSlot;

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API UInGameHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	// Widgets
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* progress_hp;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* HorizontalBox_Skill;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* HorizontalBox_BuffSkill;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Skill_Slot_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Skill_Slot_2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Skill_Slot_3;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* Skill_Slot_4;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Guide;

	// Animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Animation_Heal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Animation_Heal_Progress;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Anim_Skill_Unable_1;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Anim_Skill_Unable_2;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Anim_Skill_Unable_3;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Anim_Skill_Unable_4;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Anim_Warning_Show;

private:
	UPROPERTY(EditAnywhere, Category = CustomUISlot)
	TSubclassOf<UBuffCoolTimeSlot> m_BuffCoolTimeSlot_Class;


private:
	// TpsCharacter
	ATpsCharacter* m_pPlayerChar;

private:
	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void BindSkill();
	void EditHpProgress(float currentHp, bool isHeal);

public:
	void AddBuffCoolTime(class UBaseSkillComponent* skillComp);

public:
	UUMGSequencePlayer* PlayAnim_Show_WarningText(const FString& strWarning);

	UUMGSequencePlayer* PlayAnim_SkillUnable_1(const FString& strReason);
	UUMGSequencePlayer* PlayAnim_SkillUnable_2(const FString& strReason);
	UUMGSequencePlayer* PlayAnim_SkillUnable_3(const FString& strReason);
	UUMGSequencePlayer* PlayAnim_SkillUnable_4(const FString& strReason);

};
