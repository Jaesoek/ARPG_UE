// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuffCoolTimeSlot.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API UBuffCoolTimeSlot : public UUserWidget
{
	GENERATED_BODY()

	friend class UInGameHUD;

private:
	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	float m_fBuffTime;

	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	UTexture2D* m_ptrTexture;

public:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE float GetBuffTime() { return m_fBuffTime; };
	FORCEINLINE void SetBuffTime(float buffTime) { m_fBuffTime = buffTime; };
};
