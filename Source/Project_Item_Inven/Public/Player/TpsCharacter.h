
#pragma once

#include "Project_Item_Inven.h"
#include "GameFramework/Character.h"
#include "TpsCharacter.generated.h"

DECLARE_DELEGATE(FOnCharacterMove);
DECLARE_DELEGATE(FCharacterMoveOnlyMouse);
DECLARE_DELEGATE(FCharacterMoveOnlyKey);

UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API ATpsCharacter : public ACharacter
{
	GENERATED_BODY()

	friend class AInGamePlayerController;

private:
	// TravelMode Camera Components
	UPROPERTY(VisibleAnyWhere, Category = Camera)
	class USpringArmComponent* m_TravelSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = true))
	class UChildActorComponent* m_TravelChildComponent;

	// TpsMode Camera Components
	UPROPERTY(VisibleAnyWhere, Category = Camera)
	class USpringArmComponent* m_TpsSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = true))
	class UChildActorComponent* m_TpsChildComponent;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	/** For targeting mode */
	bool m_bTargetingMode;
	UPROPERTY(EditAnywhere, Category = Targeting)
	class UTargetingComp* m_TargetingComp;

private:
	/** Input right only for assignment */
	float m_fInputRight;
	/** only for assignment */
	float m_fInputForward;

public:
	FOnCharacterMove OnCharacterMove;

public:
	FORCEINLINE class UCharacterStatComp* GetCharacterStat() { return m_CharacterStatComp; };

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Equip, Meta = (AllowPrivateAccess = true))
	class AEquipItem* m_CurrentWeapon;

private:
	UPROPERTY(EditAnywhere, Category = Animation)
	UAnimMontage* m_DodgeAnimation;

private: // Control with animation asset
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool isAttackable;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool isDashable;

	FTimerHandle m_TimerHandle_Sprint;

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
	void Dash_Pressed();
	void Dash_Released();

	void Attack();

	void Skill1_Pressed();
	void Skill1_Released();
	void Skill2_Pressed();
	void Skill2_Released();
	void Skill3_Pressed();
	void Skill3_Released();
	void Skill4_Pressed();
	void Skill4_Released();

	void FocusEnemyOnOff();
	void FocusEnemySwitch();

//////////////////////////////////////////////////////////////////////////////////////////////////

public:
	bool Equip(TSubclassOf<AEquipItem> equipItemClass);
	void UnEquip(EEquipType equipType);

	UFUNCTION(BlueprintCallable)
	void SwapSkill(int nFristIndex, int nSecondIndex);

protected:
	void WeaponSwitchRifle();
	void WeaponSwitchSword();
	void WeaponSwitchNoWeapon();

public:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	FORCEINLINE const EWeaponMode GetWeaponMode() const { return m_eWeaponMode; }
	FORCEINLINE void SetWeaponMode(EWeaponMode weaponType) { m_eWeaponMode = weaponType; }

public: // Camera mode setting
	UFUNCTION(BlueprintCallable)
	void SetTpsMode();

	UFUNCTION(BlueprintCallable)
	void SetTravelMode();
};
