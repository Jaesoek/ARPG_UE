// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"
#include "UI/SkillSlot.h"
#include "UI/BuffCoolTimeSlot.h"

#include "Components/ProgressBar.h"
#include "Components/HorizontalBox.h"

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

void _BindSkillLogic(UBaseSkillComponent* skillComp, USkillSlot* skillSlot)
{
	if (IsValid(skillComp))
	{
		skillComp->OnCoolTIme().AddUObject(skillSlot, &USkillSlot::UpdateCoolTimePercent);
		skillComp->RefreshCoolTimeDelegate();
		skillSlot->SetSlotIcon(skillComp->m_Texture);
	}
	else
	{
		skillSlot->UpdateCoolTimePercent(0.f);
		skillSlot->SetSlotIcon(nullptr);
	}
}

void UInGameHUD::BindSkill()
{
	if (!IsValid(m_pPlayerChar)) return;
	_BindSkillLogic(m_pPlayerChar->m_arrSKillComp[0], Skill_Slot_1);
	_BindSkillLogic(m_pPlayerChar->m_arrSKillComp[1], Skill_Slot_2);
	_BindSkillLogic(m_pPlayerChar->m_arrSKillComp[2], Skill_Slot_3);
	_BindSkillLogic(m_pPlayerChar->m_arrSKillComp[3], Skill_Slot_4);
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
}

UUMGSequencePlayer* UInGameHUD::PlayAnimSkillCoolTime1()
{
	return PlayAnimation(Anim_Skill_CoolTime_1);
}
UUMGSequencePlayer* UInGameHUD::PlayAnimSkillCoolTime2()
{
	return PlayAnimation(Anim_Skill_CoolTime_2);
}
UUMGSequencePlayer* UInGameHUD::PlayAnimSkillCoolTime3()
{
	return PlayAnimation(Anim_Skill_CoolTime_3);
}
UUMGSequencePlayer* UInGameHUD::PlayAnimSkillCoolTime4()
{
	return PlayAnimation(Anim_Skill_CoolTime_4);
}

