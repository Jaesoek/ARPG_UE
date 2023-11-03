// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComp.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ITEM_INVEN_API UCharacterStatComp : public UActorComponent
{
	GENERATED_BODY()

	// It can't used alone
	friend class ATpsCharacter;
	friend class ABaseEnemy;

protected:
	float m_HpCurrent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Stat", meta = (ClampMin = "0.0", UIMin = "100.0"))
	float m_HpMax_Base;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Base Stat", meta = (ClampMin = "0.0", UIMin = "10.0"))
	float m_HpRecovery_Base;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Base Stat", meta = (ClampMin = "0", UIMin = "20"))
	int m_ATK_Base;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Base Stat", meta = (ClampMin = "0", ClampMax = "100", UIMin = "10"))
	int m_CriticalRate_Base;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Base Stat", meta = (ClampMin = "0", UIMin = "50"))
	int m_CriticalDamage_Base;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Base Stat", meta = (ClampMin = "0.2", UIMin = "1.0"))
	float m_AttackSpeed_Base;

	TMap<FString, float> m_mapHpMax;
	TMap<FString, float> m_mapHpRecovery;
	TMap<FString, int> m_mapATKMax;
	TMap<FString, int> m_mapCriticalRate;
	TMap<FString, int> m_mapCriticalDamage;
	TMap<FString, float> m_mapAttackSpeed;

private:
	float m_fSumDeltaTimeForHpRecovery;

public:
	UCharacterStatComp();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE float GetHp() const { return m_HpCurrent; }

	UFUNCTION(BlueprintCallable)
	float GetMaxHp() const;
	
	UFUNCTION(BlueprintCallable)
	float GetHpRecovery() const;
	
	UFUNCTION(BlueprintCallable)
	int GetATK() const;
	
	UFUNCTION(BlueprintCallable)
	int GetCriticalRate() const;
	
	UFUNCTION(BlueprintCallable)
	int GetCriticalDmg() const;

	UFUNCTION(BlueprintCallable)
	float GetAttackSpeed() const;

public:
	UFUNCTION(BlueprintCallable)
	float AddHp(float heal);
	
	UFUNCTION(BlueprintCallable)
	float ReduceHp(float damage);

	UFUNCTION(BlueprintCallable)
	float AddAttackSpeed(FString name, float attackSpeed);

	UFUNCTION(BlueprintCallable)
	float ClearAttackSpeed(FString name);

public:
	DECLARE_EVENT_TwoParams(UCharacterStatComp, FHpChangeDelegate, float, bool);
	FHpChangeDelegate& OnHpChanged() { return m_OnHpChanged; }
private:
	FHpChangeDelegate m_OnHpChanged;

};
