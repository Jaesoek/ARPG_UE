// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/BaseSkillComponent.h"
#include "Player/TpsCharacter.h"

UBaseSkillComponent::UBaseSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBaseSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// Cool time init
	SetCoolTime(m_fMaxCoolTime);
}

void UBaseSkillComponent::PostLoad()
{
	Super::PostLoad();

	m_OwnerCharcter = GetOwner<ATpsCharacter>();
}

const float UBaseSkillComponent::GetCoolTime() const
{
	return m_fCoolTime;
}

void UBaseSkillComponent::SetCoolTime(float fCoolTime)
{
	m_fCoolTime = fCoolTime;
	m_OnCoolTime.Broadcast(m_fCoolTime / m_fMaxCoolTime);
}

void UBaseSkillComponent::RefreshCoolTimeDelegate()
{
	m_OnCoolTime.Broadcast(m_fCoolTime / m_fMaxCoolTime);
}

bool UBaseSkillComponent::ActivateSkill(FString& strUnableReason)
{
	check(0 && "You must override this");
	return false;
}

bool UBaseSkillComponent::ReleasedSkill()
{
	check(0 && "You must override this");
	return false;
}

void UBaseSkillComponent::CastingSkill()
{
	check(0 && "You must override this");
}