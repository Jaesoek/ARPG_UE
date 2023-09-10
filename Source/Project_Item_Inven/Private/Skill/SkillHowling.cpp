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


bool USkillHowling::ActivateSkill(FString& strUnableReason)
{
	if (m_fMaxCoolTime > m_fCoolTime)
	{
		strUnableReason += FString(TEXT("Cool time issue!"));
		return false;
	}
	else if (m_OwnerCharcter->GetCharacterStat()->GetHp() < m_fSkillCost)
	{
		strUnableReason += FString(TEXT("Not enough HP"));
		return false;
	}

	SetCoolTime(0.f);
	m_OwnerCharcter->PlayAnimMontage(m_AnimMontage);
	m_OwnerCharcter->GetCharacterStat()->ReduceHp(m_fSkillCost);
	m_OwnerCharcter->GetCharacterStat()->AddAttackSpeed(m_SkillName, 0.5f);

	m_OwnerCharcter->GetWorldTimerManager().SetTimer(
		m_TimerHandle_Buff, this, &USkillHowling::ReleaseBuff, m_fBuffTime, false
	);
	m_OwnerCharcter->GetWorldTimerManager().GetTimerRemaining(m_TimerHandle_Buff);

	return true;
}

bool USkillHowling::ReleasedSkill()
{
	return false;
}

void USkillHowling::CastingSkill()
{
	
}

// 해제가 처리해야할것들
//  -> UI에서 제거하기
//  -> Character Effect 제거하기

//  -> Stat에서 제거하기 (O)
void USkillHowling::ReleaseBuff()
{
	m_OwnerCharcter->GetWorldTimerManager().ClearTimer(m_TimerHandle_Buff);

	m_OwnerCharcter->GetCharacterStat()->ClearAttackSpeed(m_SkillName);
}
