// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CharacterStatComp.h"

UCharacterStatComp::UCharacterStatComp()
{
	PrimaryComponentTick.bCanEverTick = true;

	m_mapHpMax = TMap<FString, float>{};
	m_mapHpRecovery = TMap<FString, float>{};
	m_mapATKMax = TMap<FString, int>{};
	m_mapCriticalRate = TMap<FString, int>{};
	m_mapCriticalDamage = TMap<FString, int>{};
	m_mapAttackSpeed = TMap<FString, float>{};
}


void UCharacterStatComp::BeginPlay()
{
	Super::BeginPlay();

}


void UCharacterStatComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetMaxHp() > GetHp()) // Auto recovery
		AddHp(GetHpRecovery() * DeltaTime);
}

float UCharacterStatComp::GetMaxHp() const
{
	float result = m_HpMax_Base;
	for (const auto& HpBuff : m_mapHpMax)
		result += HpBuff.Value;
	return result;
}

float UCharacterStatComp::GetHpRecovery() const
{
	float result = m_HpRecovery_Base;
	for (const auto& HpRecovBuff : m_mapHpRecovery)
	{
		result += HpRecovBuff.Value;
	}
	return result;
}

int UCharacterStatComp::GetATK() const
{
	int result = m_ATK_Base;
	for (const auto& ATKBuff : m_mapATKMax)
		result += ATKBuff.Value;
	return result;
}

int UCharacterStatComp::GetCriticalRate() const
{
	int result = m_CriticalRate_Base;
	for (const auto& CriRateBuff : m_mapCriticalRate)
		result += CriRateBuff.Value;
	if (result > 100) result = 100;
	return result;
}

int UCharacterStatComp::GetCriticalDmg() const
{
	int result = m_CriticalDamage_Base;
	for (const auto& CriDmgBuff : m_mapCriticalDamage)
		result += CriDmgBuff.Value;
	return result;
}

float UCharacterStatComp::GetAttackSpeed() const
{
	float result = m_AttackSpeed_Base;
	for (const auto& AttackSpeedBuff : m_mapAttackSpeed)
		result += AttackSpeedBuff.Value;
	return result;
}

float UCharacterStatComp::AddHp(float heal)
{
	m_HpCurrent = FMath::Clamp<float>(m_HpCurrent + heal, 0.f, GetMaxHp());
	m_OnHpChanged.Broadcast(m_HpCurrent, true);
	return m_HpCurrent;
}

float UCharacterStatComp::ReduceHp(float damage)
{
	m_HpCurrent = FMath::Clamp<float>(m_HpCurrent - damage, 0.f, GetMaxHp());
	m_OnHpChanged.Broadcast(m_HpCurrent, false);
	return m_HpCurrent;
}

float UCharacterStatComp::AddAttackSpeed(FString name, float attackSpeed)
{
	m_mapAttackSpeed.Add(TTuple<FString, float>{name, attackSpeed});
	return GetAttackSpeed();
}

float UCharacterStatComp::ClearAttackSpeed(FString name)
{
	m_mapAttackSpeed.Remove(name);
	return GetAttackSpeed();
}