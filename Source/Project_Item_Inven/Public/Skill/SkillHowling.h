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

private:
	FTimerHandle m_TimerHandle_Buff;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Detail")
	float m_fBuffTime;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Detail")
	class UNiagaraSystem* m_effect;

	bool m_isBuffActive;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual bool ActivateSkill(FString& strUnableReason) override;
	virtual bool ReleasedSkill() override;
protected:
	virtual void CastingSkill() override;

private:
	UFUNCTION()
	void ReleaseBuff();
};
