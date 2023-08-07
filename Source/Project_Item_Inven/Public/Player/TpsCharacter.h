
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TpsCharacter.generated.h"

UENUM(BlueprintType)
enum class EWeaponMode : uint8
{
	Default, Sword, Rifle
};

UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API ATpsCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnyWhere, Category = Camera)
	class USpringArmComponent* m_TpsSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = true))
	class UChildActorComponent* m_TpsChildComponent;

	UPROPERTY(VisibleAnyWhere, Category = Camera)
	class USpringArmComponent* m_TravelSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = true))
	class UChildActorComponent* m_TravelChildComponent;

	UPROPERTY(VisibleAnyWhere, Category = Targeting)
	class UTargetingComp* m_TargetingComp;

public:
	ATpsCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float NewAxisValue);
	void LookUp(float NewAxisValue);

	void SwitchWeapon();
	void FocusEnemy();

private:
	EWeaponMode m_eWeaponMode;
public:
	UFUNCTION(BlueprintCallable)
	EWeaponMode GetWeaponMode() const { return m_eWeaponMode; }
	UFUNCTION(BlueprintCallable)
	void SetWeaponMode(EWeaponMode weaponMode) { m_eWeaponMode = weaponMode; }

public:
	void SetTpsMode();
	void SetTravelMode();

};
