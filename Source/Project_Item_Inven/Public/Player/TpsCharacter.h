
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

	UPROPERTY(EditAnywhere, Category = Targeting)
	class UTargetingComp* m_TargetingComp;

	// Helmet actor component for equipment
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equip, Meta = (AllowPrivateAccess = true))
	class UChildActorComponent* m_HelmetActorComp;

	// Breast actor component for equipment
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equip, Meta = (AllowPrivateAccess = true))
	class UChildActorComponent* m_BreastActorComp;

	// Weapon actor component for equipment
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equip, Meta = (AllowPrivateAccess = true))
	class UChildActorComponent* m_WeaponActorComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, Meta = (AllowPrivateAccess = true))
	class UCharacterStatComp* m_CharacterStatComp;

	UPROPERTY(EditAnywhere, Category = Skill)
	TArray<class UBaseSkillComponent*> m_arrSKill;

	/** For targeting mode */
	bool m_bTargetingMode;

private:
	/** Input right */
	float m_fInputRight;
	/** Input forward */
	float m_fInputForward;

private:
	UPROPERTY(EditAnywhere, Category = Animation)
	UAnimMontage* m_RollAnimation;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Equip, Meta = (AllowPrivateAccess = true))
	EWeaponMode m_eWeaponMode;
public:
	FORCEINLINE const EWeaponMode GetWeaponMode() const { return m_eWeaponMode; }
	FORCEINLINE void SetWeaponMode(EWeaponMode weaponMode) { m_eWeaponMode = weaponMode; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Equip, Meta = (AllowPrivateAccess = true))
	class AEquipItem* m_CurrentWeapon;

public:
	ATpsCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float NewAxisValue);
	void LookUp(float NewAxisValue);

	void Dash();

	void Attack();

	void Skill1();
	void Skill2();
	void Skill3();
	void Skill4();

	void Equip(TSubclassOf<AEquipItem> equipItemClass);

	void WeaponSwitchRifle();
	void WeaponSwitchSword();

	void FocusEnemyOnOff();
	void FocusEnemySwitch();

public:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private: // Camera mode setting
	void SetTpsMode();
	void SetTravelMode();

};
