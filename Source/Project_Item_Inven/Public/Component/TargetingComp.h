// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TargetingComp.generated.h"

/** Only for ACharacter */
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ITEM_INVEN_API UTargetingComp : public USceneComponent
{
	GENERATED_BODY()

public:	
	UTargetingComp();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	ACharacter* m_OwnerChar;

	TSet<AActor*> m_setTargetActors;

	UPROPERTY(EditAnywhere, Category = TargetMark)
	TSubclassOf<AActor> m_class_TargetMark;
	AActor* m_TargetMark;


private:
	AActor* m_TargetedActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Targeting, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* TargetingSphere;

	UFUNCTION()
	void OnTargetingOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndTargetingOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:
	bool FocusTarget();
	void SwitchFocusedTarget();
};
