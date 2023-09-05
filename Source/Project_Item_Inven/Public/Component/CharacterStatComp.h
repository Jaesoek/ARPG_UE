// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComp.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ITEM_INVEN_API UCharacterStatComp : public UActorComponent
{
	GENERATED_BODY()

	// It can't created alone
	friend class ATpsCharacter;

public:	
	UCharacterStatComp();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	int m_HpCurrent;

	UPROPERTY(EditAnywhere, Category = "Base Stat", meta = (ClampMin = "0", UIMin = "0"))
	int m_HpMax_Base;

	UPROPERTY(EditDefaultsOnly, Category = "Base Stat", meta = (ClampMin = "0", UIMin = "0"))
	int m_ATK_Base;

	UPROPERTY(EditDefaultsOnly, Category = "Base Stat", meta = (ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax = "100"))
	int m_CriticalRate_Base;

	UPROPERTY(Transient, EditDefaultsOnly, Category = "Base Stat", meta = (ClampMin = "0", UIMin = "0"))
	int m_CriticalDamage_Base;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Base Stat", meta = (ClampMin = "0.2", UIMin = "1.0", AllowPrivateAccess = true))
	float m_AttackSpeed_Base;

	TMap<FString, int> m_mapHpMax;
	TMap<FString, int> m_mapATKMax;
	TMap<FString, int> m_mapCriticalRate;
	TMap<FString, int> m_mapCriticalDamage;
	TMap<FString, float> m_mapAttackSpeed;

public:
	FORCEINLINE int GetHp() const { return m_HpCurrent; }

	int GetMaxHp() const;
	int GetATK() const;
	int GetCriticalRate() const;
	int GetCriticalDmg() const;
	UFUNCTION(BlueprintCallable)
	float GetAttackSpeed() const;

public:
	// Return remain Hp
	int AddHp(int heal);
	// Return remain Hp
	int ReduceHp(int damage);

	UFUNCTION(BlueprintCallable)
	float AddAttackSpeed(FString name, float attackSpeed);

	UFUNCTION(BlueprintCallable)
	float ClearAttackSpeed(FString name);

public:
	DECLARE_EVENT_TwoParams(UCharacterStatComp, FHpChangeDelegate, int, bool);
	FHpChangeDelegate& OnHpChanged() { return m_OnHpChanged; }
private:
	FHpChangeDelegate m_OnHpChanged;

};
