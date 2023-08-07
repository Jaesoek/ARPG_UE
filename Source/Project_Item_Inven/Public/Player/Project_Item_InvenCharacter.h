// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_Item_InvenCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnMouseTurn);

UCLASS(config=Game)
class AProject_Item_InvenCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AProject_Item_InvenCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;

protected: // Called for character, camera move
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float NewAxisValue);
	void LookUp(float NewAxisValue);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

////////////////////////////////////////////////////////////////////////////////
private: // For Interaction
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* InteractionSphere;

protected: // Interaction KeyEvent 대응 EventFuction
	void Interaction();

private: // Interaction 관련 내용
	// Focus 여부 결정 대응 EventFuction
	UFUNCTION()
	void OnInteractionOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndInteractionOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta= (AllowPrivateAccess = true))
	AActor* InteractiveActor;

	// Focus시 출력될 UI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction_UI,Meta= (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> Interaction_Class;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction_UI, Meta = (AllowPrivateAccess = true))
	class UUserWidget* ptrInteractionIndicator;

////////////////////////////////////////////////////////////////////////////////
protected: // 공격 관련 내용
	void RangeSkillStart();
	void RangeSkillCasting();
	void RangeSkillFire();

	// For range check
	class ADecalActor* CheckRangeDecalActor;

	UPROPERTY(EditAnywhere, Category = DecalRangeCheck)
	class UMaterial* M_RangeCheck;
	class UMaterialInstanceDynamic* MID_RangeCheck;

private:
	UPROPERTY(EditAnywhere, Category = AnimMontage)
	class UAnimMontage* m_Montage;

public:
	// TODO: Movement 도 적용해야하기 때문에 지금 이걸로는 조금 약함
	FOnMouseTurn OnMouseTurn;


////////////////////////////////////////////////////////////////////////////////
private: //  TODO: For Targeting
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyTargeting, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* TargetingSphere;

	UFUNCTION()
	void OnTargetingOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndTargetingOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private: // For Monster Targeting
	void TargetingEnemy();

	class ABaseEnemy* m_pTargetedEnemy;

	UPROPERTY()
	TSet<class ABaseEnemy*> m_setTargetable;
};

