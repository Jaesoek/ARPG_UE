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
	class UBorder* border_profile;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* img_profile;
	
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
	class UWidgetAnimation* Animation_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Animation_Heal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Animation_Heal_Progress;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Anim_Skill_CoolTime_1;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Anim_Skill_CoolTime_2;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Anim_Skill_CoolTime_3;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Anim_Skill_CoolTime_4;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Anim_Guide_Show;

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
	UUMGSequencePlayer* PlayAnimSkillCoolTime1();
	UUMGSequencePlayer* PlayAnimSkillCoolTime2();
	UUMGSequencePlayer* PlayAnimSkillCoolTime3();
	UUMGSequencePlayer* PlayAnimSkillCoolTime4();

};
