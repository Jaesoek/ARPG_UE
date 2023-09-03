
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

	friend class AInGamePlayerController;

private:
	// Camera Components
	UPROPERTY(VisibleAnyWhere, Category = Camera)
	class USpringArmComponent* m_TpsSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = true))
	class UChildActorComponent* m_TpsChildComponent;

	UPROPERTY(VisibleAnyWhere, Category = Camera)
	class USpringArmComponent* m_TravelSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = true))
	class UChildActorComponent* m_TravelChildComponent;


	// Helmet actor component for equipment
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equip, Meta = (AllowPrivateAccess = true))
	class UChildActorComponent* m_HelmetActorComp;

	// Breast actor component for equipment
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equip, Meta = (AllowPrivateAccess = true))
	class UChildActorComponent* m_BreastActorComp;

	// Weapon actor component for equipment
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equip, Meta = (AllowPrivateAccess = true))
	class UChildActorComponent* m_WeaponActorComp;


	// ActorComponents
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, Meta = (AllowPrivateAccess = true))
	class UCharacterStatComp* m_CharacterStatComp;

	UPROPERTY(EditAnywhere, Category = Targeting)
	class UTargetingComp* m_TargetingComp;


	/** For targeting mode */
	bool m_bTargetingMode;

private:
	/** Input right */
	float m_fInputRight;
	/** Input forward */
	float m_fInputForward;


public: // Skill List
	UPROPERTY(EditAnywhere, Category = Skill)
	TArray<class UBaseSkillComponent*> m_arrSKillComp;

	DECLARE_EVENT(ATpsCharacter, FSkillChangeDelegate);
	FSkillChangeDelegate& OnSkillChanged() { return m_OnSkillChanged; }

private:
	FSkillChangeDelegate m_OnSkillChanged;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Equip, Meta = (AllowPrivateAccess = true))
	EWeaponMode m_eWeaponMode;

public:
	FORCEINLINE const EWeaponMode GetWeaponMode() const { return m_eWeaponMode; }
	FORCEINLINE void SetWeaponMode(EWeaponMode weaponMode) { m_eWeaponMode = weaponMode; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Equip, Meta = (AllowPrivateAccess = true))
	class AEquipItem* m_CurrentWeapon;

	UPROPERTY(EditAnywhere, Category = Animation) // TODO: 언젠간 어디로 옮겨야하는디...
	UAnimMontage* m_RollAnimation;


public:
	ATpsCharacter();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected: // Logics about key,mouse Input
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float NewAxisValue);
	void LookUp(float NewAxisValue);

	void Dash();

	void Attack();

	void Skill1_Pressed();
	void Skill1_Repeat();
	void Skill1_Released();
	void Skill2_Pressed();
	void Skill2_Repeat();
	void Skill2_Released();
	void Skill3();
	void Skill4();

protected: // Logics about key,mouse Input
	void Equip(TSubclassOf<AEquipItem> equipItemClass);

	void WeaponSwitchRifle();
	void WeaponSwitchSword();

	void FocusEnemyOnOff();
	void FocusEnemySwitch();

public:
	class UCharactrStat* GetCharacterStat() const;

public:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private: // Camera mode setting
	void SetTpsMode();
	void SetTravelMode();

};
