// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ITEM_INVEN_API UEnemyHpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* progress_hp;

	void BindingHp();
};
