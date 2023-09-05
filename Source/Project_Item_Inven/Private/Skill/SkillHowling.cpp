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
	{
		return false;
	}

	SetCoolTime(0.f);
	m_OwnerCharcter->PlayAnimMontage(m_AnimMontage);
	m_OwnerCharcter->GetCharacterStat()->AddAttackSpeed(m_SkillName, 0.5f);
	return true;
}

bool USkillHowling::ReleasedSkill()
{
	return false;
}

void USkillHowling::CastingSkill()
{
	
}
