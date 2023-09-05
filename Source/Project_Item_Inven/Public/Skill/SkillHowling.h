// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/BaseSkillComponent.h"
#include "SkillHowling.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API USkillHowling : public UBaseSkillComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual bool ActivateSkill() override;
	virtual bool ReleasedSkill() override;
protected:
	virtual void CastingSkill() override;

};
