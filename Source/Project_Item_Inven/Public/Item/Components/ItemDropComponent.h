// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemDropComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ITEM_INVEN_API UItemDropComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = DropAnimation, Meta = (AllowPrivateAccess = true))
	class UCurveFloat* m_CurveSizeFloat;

	UPROPERTY(EditAnywhere, Category = DropAnimation, Meta = (AllowPrivateAccess = true, UIMin = 50, UIMax = 1000))
	unsigned int m_uMaxDropRadius;

private:
	float m_fDropTime;

	FVector m_StartPosition;
	FVector m_DropPosition;

	enum class EItemStatus
	{
		None, Dropping, Dropped
	};
	EItemStatus m_eItemStatus;

public:
	UItemDropComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void setStatus(EItemStatus eStatus);
};
