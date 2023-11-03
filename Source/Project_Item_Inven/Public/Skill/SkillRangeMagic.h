// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/BaseSkillComponent.h"
#include "SkillRangeMagic.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API USkillRangeMagic : public UBaseSkillComponent
{
	GENERATED_BODY()

private:
	bool m_isCasting;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Detail")
	class UMaterial* m_M_RangeCheck;

	class UMaterialInstanceDynamic* m_MID_RangeCheck;
	class ADecalActor* m_DA_RangeCheck;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Detail")
	class UNiagaraSystem* m_NS_Attack;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Detail", Meta = (UIMin = "0.0", UIMax = "160.0", ClampMin = "0.0", ClampMax = "160.0"))
	float m_AttackRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Detail", Meta = (UIMin = "0.0", UIMax = "80.0", ClampMin = "0.0", ClampMax = "80.0"))
	float m_DamageSkill;

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual bool ActivateSkill(FString& strUnableReason) override;
	virtual bool ReleasedSkill() override;
protected:
	virtual void CastingSkill() override;
};
