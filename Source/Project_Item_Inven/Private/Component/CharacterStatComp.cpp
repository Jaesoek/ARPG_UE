// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CharacterStatComp.h"

UCharacterStatComp::UCharacterStatComp()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCharacterStatComp::BeginPlay()
{
	Super::BeginPlay();

}


void UCharacterStatComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

int UCharacterStatComp::AddHp(int heal)
{
	m_HpCurrent = FMath::Clamp<int>(m_HpCurrent + heal, 0, m_HpMax);

	m_OnHpChanged.Broadcast(m_HpCurrent, true);
	return m_HpCurrent;
}

int UCharacterStatComp::ReduceHp(int damage)
{
	m_HpCurrent = FMath::Clamp<int>(m_HpCurrent - damage, 0, m_HpMax);

	m_OnHpChanged.Broadcast(m_HpCurrent, false);
	return m_HpCurrent;
}

int UCharacterStatComp::AddSp(int heal)
{
	return m_SpCurrent;
}

int UCharacterStatComp::ReduceSp(int damage)
{
	return m_SpCurrent;
}

int UCharacterStatComp::AddAttackSpeed(int attackSpeed)
{
	return m_AttackSpeed;
}

int UCharacterStatComp::ReduceAttackSpeed(int attackSpeed)
{
	return m_AttackSpeed;
}
