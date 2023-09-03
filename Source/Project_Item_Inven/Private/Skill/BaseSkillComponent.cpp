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

void UBaseSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_IsCasting)
	{
		// Cool time
		if (m_fCoolTime < m_fMaxCoolTime)
		{
			SetCoolTime(m_fCoolTime + DeltaTime);
		}
		else if (m_fCoolTime >= m_fMaxCoolTime)
		{
			SetCoolTime(m_fMaxCoolTime);
		}
	}
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

bool UBaseSkillComponent::ActivateSkill_Implementation()
{
	if (m_OwnerCharcter == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("No owner"));
		return false;
	}
	else if (m_fCoolTime < m_fMaxCoolTime)
	{
		return false;
	}

	SetCoolTime(0.f);
	return true;
}

bool UBaseSkillComponent::RepeatSkill_Implementation()
{
	return true;
}

bool UBaseSkillComponent::ReleasedSkill_Implementation()
{
	if (!m_IsCasting)
	{
		return false;
	}

	m_IsCasting = false;
	return true;
}

