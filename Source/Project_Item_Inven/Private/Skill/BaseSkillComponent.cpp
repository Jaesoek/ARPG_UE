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

	// Cool time setting
	m_fCoolTime = m_fMaxCoolTime + FLT_EPSILON;
}


void UBaseSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Cool time
	if (m_fCoolTime < m_fMaxCoolTime)
	{
		m_fCoolTime += DeltaTime;
	}
	else if (m_fCoolTime >= m_fMaxCoolTime)
	{
		m_fCoolTime = m_fMaxCoolTime;
	}
}

void UBaseSkillComponent::ActivateSkill_Implementation()
{
	if (GetOwner()->GetOwner() == nullptr) return;
	else if (m_fCoolTime < m_fMaxCoolTime) return;

	m_fCoolTime = 0.f;
}

