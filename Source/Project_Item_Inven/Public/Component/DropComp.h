// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DropComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ITEM_INVEN_API UDropComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDropComp();

protected:
	virtual void PostLoad() override;
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/** Character movement component belongs to */
	UPROPERTY(Transient, DuplicateTransient)
	AActor* m_ActorOwner;
};
