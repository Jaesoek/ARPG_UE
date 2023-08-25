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
	class ATpsCharacter* m_ActorOwner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimMontage* m_AnimMontage;

	UPROPERTY(EditAnywhere, Category = Thumbnail)
	UTexture2D* m_Texture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status, Meta = (AllowPrivateAccess = true, ClampMin = "0.0", UIMin = "0.0"))
	float m_fMaxCoolTime;

	float m_fCoolTime;


public:	
	UBaseSkillComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE const float GetCoolTime() const { return m_fCoolTime; }
	FORCEINLINE void SetCoolTime(float fCoolTime) { m_fCoolTime = fCoolTime; }

public:
	UFUNCTION(BlueprintNativeEvent)
	void ActivateSkill();
	virtual void ActivateSkill_Implementation();
	
};
