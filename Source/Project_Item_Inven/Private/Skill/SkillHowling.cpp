// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillHowling.h"
#include "Player/TpsCharacter.h"
#include "Component/CharacterStatComp.h"


void USkillHowling::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_fMaxCoolTime > m_fCoolTime)
	{
		if (m_fMaxCoolTime <= m_fCoolTime + DeltaTime)
			SetCoolTime(m_fMaxCoolTime);
		else
			SetCoolTime(m_fCoolTime + DeltaTime);
	}
}


bool USkillHowling::ActivateSkill()
{
	if (m_fMaxCoolTime > m_fCoolTime)
		return false;
	else if (m_OwnerCharcter->GetCharacterStat()->GetHp() < m_fSkillCost)
		return false;

	SetCoolTime(0.f);
	m_OwnerCharcter->PlayAnimMontage(m_AnimMontage);
	m_OwnerCharcter->GetCharacterStat()->ReduceHp(m_fSkillCost);
	m_OwnerCharcter->GetCharacterStat()->AddAttackSpeed(m_SkillName, 0.5f);

	// TODO: Timer 동작하도록 설정

	return true;
}

bool USkillHowling::ReleasedSkill()
{
	return false;
}

void USkillHowling::CastingSkill()
{
	
}
