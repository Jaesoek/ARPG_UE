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

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual bool ActivateSkill(FString& strUnableReason) override;
	virtual bool ReleasedSkill() override;
protected:
	virtual void CastingSkill() override;
};
