// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractComp.generated.h"


/** Only for ACharacter */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_ITEM_INVEN_API UInteractComp : public USceneComponent
{
	GENERATED_BODY()

protected:
	ACharacter* m_OwnerChar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Targeting, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* m_InteractSphere;

	TSet<AActor*> m_setInteractableActor;


public:	
	UInteractComp();

protected:
	virtual void BeginPlay() override;


protected:
	UFUNCTION()
	void OnInteractOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndInteractOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		
};
