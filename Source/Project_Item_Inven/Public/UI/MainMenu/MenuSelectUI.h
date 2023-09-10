// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSelectUI.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API UMenuSelectUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* Border_Select;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock_Select;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Anim_Focused;

private:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	// TODO: Init 추가하기
	void Init(const UObject* object, );
};
