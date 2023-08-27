// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipItem.generated.h"

UCLASS()
class PROJECT_ITEM_INVEN_API AEquipItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AEquipItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* m_AttackMontage;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Skill, Meta = (AllowPrivateAccess = true))
	class UBaseSkillComponent* m_SkillComp;

public:
	FORCEINLINE UAnimMontage* GetAttackMontage() const
	{
		return m_AttackMontage;
	};
	FORCEINLINE void SetAttackMontage(UAnimMontage* attackMontage)
	{
		m_AttackMontage = attackMontage;
	};
};
