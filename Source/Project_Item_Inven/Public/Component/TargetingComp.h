// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TargetingComp.generated.h"

/** Only for ACharacter */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

private:
	bool m_bFocused;
public:
	FORCEINLINE bool GetIsFocused() const { return m_bFocused; };
	FORCEINLINE void SetIsFocused(bool isFocus) { m_bFocused = isFocus; };

private:
	AActor* m_TargetActor{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Targeting, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* TargetingSphere;

	UFUNCTION()
	void OnTargetingOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndTargetingOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
