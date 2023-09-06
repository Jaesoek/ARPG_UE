// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseSkillComponent.generated.h"

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Default, Buff, Casting
};

UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ITEM_INVEN_API UBaseSkillComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	class ATpsCharacter* m_OwnerCharcter;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Skill Info")
	ESkillType m_eSkillType;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Info")
	FString m_SkillName;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Info")
	FString m_SkillDescription;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Info")
	UAnimMontage* m_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Info")
	UTexture2D* m_Texture;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Info", Meta = (ClampMin = "0.0", UIMin = "0.0"))
	float m_fSkillCost;

public:
	DECLARE_EVENT_OneParam(UBaseSkillComponent, FCoolTimeDelegate, float);
	FCoolTimeDelegate& OnCoolTIme() { return m_OnCoolTime; }
protected:
	FCoolTimeDelegate m_OnCoolTime;

	float m_fCoolTime;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Info", Meta = (ClampMin = "0.0", UIMin = "0.0"))
	float m_fMaxCoolTime;

public:	
	UBaseSkillComponent();

protected:
	virtual void BeginPlay() override;
	virtual void PostLoad() override;

public:
	const float GetCoolTime() const;
	void SetCoolTime(float fCoolTime);
	void RefreshCoolTimeDelegate();

public:
	virtual bool ActivateSkill();
	virtual bool ReleasedSkill();
protected:
	virtual void CastingSkill();
};
