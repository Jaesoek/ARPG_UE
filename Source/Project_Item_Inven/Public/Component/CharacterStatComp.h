// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComp.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ITEM_INVEN_API UCharacterStatComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStatComp();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	int m_HpCurrent;
	int m_SpCurrent;

	UPROPERTY(EditAnywhere, Category = Status, meta = (ClampMin = "0.0", UIMin = "0.0"))
	int m_HpMax;

	UPROPERTY(Transient, EditDefaultsOnly, Category = Status, meta = (ClampMin = "0.0", UIMin = "0.0"))
	int m_SpMax;

	UPROPERTY(Transient, EditDefaultsOnly, Category = Status, meta = (ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax = "100"))
	int m_CriticalRate;

	UPROPERTY(Transient, EditDefaultsOnly, Category = Status, meta = (ClampMin = "0", UIMin = "0"))
	int m_CriticalDamage;

	UPROPERTY(Transient, EditDefaultsOnly, Category = Status, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float m_AttackSpeed;

public:
	FORCEINLINE int GetHp() const { return m_HpCurrent; }
	FORCEINLINE int GetSp() const { return m_SpCurrent; }
	FORCEINLINE int GetCriticalRate() const { return m_CriticalRate; }
	FORCEINLINE int GetCriticalDmg() const { return m_CriticalDamage; }
	FORCEINLINE float GetAttackSpeed() const { return m_AttackSpeed; }

	FORCEINLINE void SetHp(int hp) { m_HpCurrent = hp; }
	FORCEINLINE void SetSp(int sp) { m_SpCurrent = sp; }
	FORCEINLINE void SetCriticalRate(int criticalRate) { m_CriticalRate = criticalRate; }
	FORCEINLINE void SetCriticalDmg(int criticalDmg) { m_CriticalDamage = criticalDmg; }
	FORCEINLINE void SetAttackSpeed(float attackSpeed) { m_AttackSpeed = attackSpeed; }

public:
	// Return remain Hp
	int AddHp(int heal);
	// Return remain Hp
	int ReduceHp(int damage);

	// Return remain Sp
	int AddSp(int heal);
	// Return remain Sp
	int ReduceSp(int damage);

	// Return now Attack Speed
	int AddAttackSpeed(int attackSpeed);
	// Return now Attack Speed
	int ReduceAttackSpeed(int attackSpeed);

public:
	DECLARE_EVENT_TwoParams(UCharacterStatComp, FHpChangeDelegate, int, bool);
	FHpChangeDelegate& OnHpChanged() { return m_OnHpChanged; }

private:
	FHpChangeDelegate m_OnHpChanged;

};
