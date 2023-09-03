// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseSkillComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ITEM_INVEN_API UBaseSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = Owner, Transient)
	class ATpsCharacter* m_OwnerCharcter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimMontage* m_AnimMontage;

	UPROPERTY(EditAnywhere, Category = Thumbnail)
	UTexture2D* m_Texture;

	// CoolTime
public:
	DECLARE_EVENT_OneParam(UBaseSkillComponent, FCoolTimeDelegate, float);
	FCoolTimeDelegate& OnCoolTIme() { return m_OnCoolTime; }
private:
	FCoolTimeDelegate m_OnCoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status, Meta = (AllowPrivateAccess = true, ClampMin = "0.0", UIMin = "0.0"))
	float m_fMaxCoolTime;
	float m_fCoolTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Status, Meta = (AllowPrivateAccess = true))
	bool m_IsCasting;

	// TODO: 스킬의 기능 : Buff? 공격기 발사? 방패 소환?
	

public:	
	UBaseSkillComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PostLoad() override;

public:
	const float GetCoolTime() const;

	void SetCoolTime(float fCoolTime);

public:  // Input 에 대응되는 로직 리스트(Pressed, Repeat, Released)
	UFUNCTION(BlueprintNativeEvent)
	bool ActivateSkill();
	virtual bool ActivateSkill_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	bool RepeatSkill();
	virtual bool RepeatSkill_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	bool ReleasedSkill();
	virtual bool ReleasedSkill_Implementation();
};
