// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"
#include "UI/SkillSlot.h"
#include "UI/BuffCoolTimeSlot.h"

#include "Components/ProgressBar.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

#include "Player/TpsCharacter.h"
#include "Skill/BaseSkillComponent.h"
#include "Component/CharacterStatComp.h"


void UInGameHUD::NativeOnInitialized()
{
	OnInitialized();

	m_pPlayerChar = GetOwningPlayerPawn<ATpsCharacter>();
	m_pPlayerChar->OnSkillChanged().AddUObject(this, &UInGameHUD::BindSkill);
	if (m_pPlayerChar->GetCharacterStat())
		m_pPlayerChar->GetCharacterStat()->OnHpChanged().AddUObject(this, &UInGameHUD::EditHpProgress);
}

void UInGameHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Tick(MyGeometry, InDeltaTime);
}

void _BindSkillLogic(UBaseSkillComponent* skillComp, USkillSlot* skillSlot, const FKey& bindedKey)
{
	if (IsValid(skillComp))
	{
		skillComp->OnCoolTIme().Clear();

		skillComp->OnCoolTIme().AddUObject(skillSlot, &USkillSlot::UpdateCoolTimePercent);
		skillComp->RefreshCoolTimeDelegate();

		skillSlot->SetSlotIcon(skillComp->m_Texture);
	}
	else
	{
		skillSlot->UpdateCoolTimePercent(0.f);
		skillSlot->SetSlotIcon(nullptr);
	}

	skillSlot->SetBindedKey(bindedKey); // (UI) Skill slot key binding
}

void UInGameHUD::BindSkill()
{
	if (!IsValid(m_pPlayerChar)) return;
	_BindSkillLogic(m_pPlayerChar->m_arrSKillComp[0], QuickSlot_1, EKeys::One);
	_BindSkillLogic(m_pPlayerChar->m_arrSKillComp[1], QuickSlot_2, EKeys::Two);
	_BindSkillLogic(m_pPlayerChar->m_arrSKillComp[2], QuickSlot_3, EKeys::Three);
	_BindSkillLogic(m_pPlayerChar->m_arrSKillComp[3], QuickSlot_4, EKeys::Four);

	QuickSlot_1->m_nIndex = 0;
	QuickSlot_2->m_nIndex = 1;
	QuickSlot_3->m_nIndex = 2;
	QuickSlot_4->m_nIndex = 3;
}

void UInGameHUD::EditHpProgress(float currentHp, bool isHeal)
{
	float percent = currentHp / m_pPlayerChar->GetCharacterStat()->GetMaxHp();
	progress_hp->SetPercent(percent);
}

void UInGameHUD::AddBuffCoolTime(UBaseSkillComponent* skillComp)
{
	auto widget = CreateWidget<UBuffCoolTimeSlot>(this, m_BuffCoolTimeSlot_Class);
	widget->m_ptrTexture = skillComp->m_Texture;
	HorizontalBox_BuffSkill->AddChildToHorizontalBox(widget);

	// buff 내용이랑 바인딩을 하고 싶어
	// 어떻게 해야하지...
	// 모르겠어... 
}

UUMGSequencePlayer* UInGameHUD::PlayAnim_Show_WarningText(const FString& strWarning)
{
	TextBlock_Guide->SetText(FText::FromString(strWarning));
	return PlayAnimation(Anim_Warning_Show);
}

UUMGSequencePlayer* UInGameHUD::PlayAnim_SkillUnable_1(const FString& strReason)
{
	TextBlock_Guide->SetText(FText::FromString(strReason));
	return PlayAnimation(Anim_Skill_Unable_1);
}

UUMGSequencePlayer* UInGameHUD::PlayAnim_SkillUnable_2(const FString& strReason)
{
	TextBlock_Guide->SetText(FText::FromString(strReason));
	return PlayAnimation(Anim_Skill_Unable_2);
}

UUMGSequencePlayer* UInGameHUD::PlayAnim_SkillUnable_3(const FString& strReason)
{
	TextBlock_Guide->SetText(FText::FromString(strReason));
	return PlayAnimation(Anim_Skill_Unable_3);
}

UUMGSequencePlayer* UInGameHUD::PlayAnim_SkillUnable_4(const FString& strReason)
{
	TextBlock_Guide->SetText(FText::FromString(strReason));
	return PlayAnimation(Anim_Skill_Unable_4);
}