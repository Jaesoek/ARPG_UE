
#include "Player/TpsCharacter.h"

#include "Camera/CameraActor.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Player/InGamePlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Component/TargetingComp.h"
#include "Component/CharacterStatComp.h"

#include "Skill/BaseSkillComponent.h"
#include "Item/EquipItem.h"
#include "InGamePlayerState.h"


ATpsCharacter::ATpsCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Decal 영향 X
	GetMesh()->bReceivesDecals = false;

	// Camera Setting TravelMode
	m_TravelSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TravelSpringArm"));
	m_TravelSpringArm->bUsePawnControlRotation = true;
	m_TravelChildComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("TravelCamChildActorComp"));

	m_TravelSpringArm->SetupAttachment(RootComponent);
	m_TravelChildComponent->SetupAttachment(m_TravelSpringArm);
	m_TravelChildComponent->SetChildActorClass(ACameraActor::StaticClass());

	// Camera Setting TpsMode
	m_TpsSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TpsSpringArm"));
	m_TpsSpringArm->bUsePawnControlRotation = true;
	m_TpsChildComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("TpsCamChildActorComp"));

	m_TpsSpringArm->SetupAttachment(RootComponent);
	m_TpsChildComponent->SetupAttachment(m_TpsSpringArm);
	m_TpsChildComponent->SetChildActorClass(ACameraActor::StaticClass());
	
	// For Setting Targeting
	m_TargetingComp = CreateDefaultSubobject<UTargetingComp>(TEXT("TargetingComponent"));
	m_TargetingComp->SetupAttachment(RootComponent);

	// Setting Skill list
	m_arrSKillComp.Init(nullptr, 4);
}

void ATpsCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Default mode
	m_eWeaponMode = EWeaponMode::Default;
	SetTravelMode();

	// TODO: Hp Bar 변경
	// m_CharacterStatComp->OnHpChanged().AddUObject(this, &ATpsCharacter::);
}

void ATpsCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATpsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATpsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATpsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATpsCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ATpsCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ATpsCharacter::LookUp);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ATpsCharacter::Attack);

	PlayerInputComponent->BindAction("MouseWheel", IE_Pressed, this, &ATpsCharacter::FocusEnemySwitch);
	PlayerInputComponent->BindAction("KeyTab", IE_Pressed, this, &ATpsCharacter::FocusEnemyOnOff);

	// TODO: Roll / Sprint 구분 필요
	PlayerInputComponent->BindAction("KeyShift", IE_Pressed, this, &ATpsCharacter::Dash);
//	PlayerInputComponent->BindAction("KeyShift", IE_Released, this, &ATpsCharacter::Dash);

	PlayerInputComponent->BindAction("Key1", IE_Pressed, this, &ATpsCharacter::Skill1);
	PlayerInputComponent->BindAction("Key2", IE_Pressed, this, &ATpsCharacter::Skill2);
	PlayerInputComponent->BindAction("Key3", IE_Pressed, this, &ATpsCharacter::Skill3);
	PlayerInputComponent->BindAction("Key4", IE_Pressed, this, &ATpsCharacter::Skill4_Pressed);
	PlayerInputComponent->BindAction("Key4", IE_Repeat, this, &ATpsCharacter::Skill4_Repeat);
	PlayerInputComponent->BindAction("Key4", IE_Released, this, &ATpsCharacter::Skill4_Released);
}

void ATpsCharacter::MoveForward(float Value)
{
	m_fInputForward = Value;
	if ((Controller != nullptr) && (m_fInputForward != 0.0f)) // float 은 기본적으로 0 비교시 >< 부등호를 사용하지만 변경이 적기 때문에 걍 0.0f ==로 처리
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, m_fInputForward);
	}
}

void ATpsCharacter::MoveRight(float Value)
{
	m_fInputRight = Value;
	if ((Controller != nullptr) && (m_fInputRight != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, m_fInputRight);
	}
}

void ATpsCharacter::Turn(float NewAxisValue)
{
	if (!m_bTargetingMode && NewAxisValue != 0.0f)
	{
		AddControllerYawInput(NewAxisValue);
	}
}

void ATpsCharacter::LookUp(float NewAxisValue)
{
	if (!m_bTargetingMode && NewAxisValue != 0.0f)
	{
		AddControllerPitchInput(NewAxisValue * 0.5f);
	}
}

void ATpsCharacter::Dash()
{
	if (IsPlayingRootMotion()) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	if (abs(m_fInputForward) > 0.01 || abs(m_fInputRight) > 0.01)
	{
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * m_fInputForward;
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * m_fInputRight;
		const FVector InputDirection = ForwardDirection + RightDirection;
		SetActorRotation(UKismetMathLibrary::MakeRotFromX(InputDirection));
	}
	else
	{
		SetActorRotation(YawRotation);
	}

	PlayAnimMontage(m_RollAnimation);
}

void ATpsCharacter::Attack()
{
	if (m_CurrentWeapon != nullptr)
	{
		PlayAnimMontage(m_CurrentWeapon->GetAttackMontage()); // Item에서 가져올 수 있도록 설정
	}
}

void ATpsCharacter::Skill1()
{
	auto skillComp = m_arrSKillComp[0];
	if (skillComp == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Empty Skill"));
		return;
	}

	skillComp->ActivateSkill();
}

void ATpsCharacter::Skill2()
{
	WeaponSwitchRifle();

	auto skillComp = m_arrSKillComp[1];
	if (skillComp == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Empty Skill"));
		return;
	}
	skillComp->ActivateSkill();
}

void ATpsCharacter::Skill3()
{
	WeaponSwitchSword();

	auto skillComp = m_arrSKillComp[2];
	if (skillComp == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Empty Skill"));
		return;
	}
	skillComp->ActivateSkill();
}

void ATpsCharacter::Skill4_Pressed()
{
	auto skillComp = m_arrSKillComp[3];
	if (skillComp == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Empty Skill"));
		return;
	}
	skillComp->ActivateSkill();
}

void ATpsCharacter::Skill4_Repeat()
{
}

void ATpsCharacter::Skill4_Released()
{
}

void ATpsCharacter::Equip(TSubclassOf<AEquipItem> equipItemClass)
{


}

void ATpsCharacter::WeaponSwitchRifle()
{
	if (m_eWeaponMode != EWeaponMode::Rifle)
	{
		SetWeaponMode(EWeaponMode::Rifle);
		GetCharacterMovement()->MaxWalkSpeed = 400.f;  // 캐릭터 설정 변경
		SetTpsMode(); // 카메라 설정 변경

		auto playerState = Cast<AInGamePlayerState>(GetPlayerState());
		m_WeaponActorComp->SetChildActorClass(playerState->m_Rifle);
		m_CurrentWeapon = Cast<AEquipItem>(m_WeaponActorComp->GetChildActor());
		m_CurrentWeapon->SetOwner(this);

		m_arrSKillComp.EmplaceAt(0, m_CurrentWeapon->m_SkillComp);
	}
}

void ATpsCharacter::WeaponSwitchSword()
{
	if (m_eWeaponMode != EWeaponMode::Sword)
	{
		SetWeaponMode(EWeaponMode::Sword);
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
		SetTravelMode();

		auto playerState = Cast<AInGamePlayerState>(GetPlayerState());
		m_WeaponActorComp->SetChildActorClass(playerState->m_Sword);
		m_CurrentWeapon = Cast<AEquipItem>(m_WeaponActorComp->GetChildActor());
		m_CurrentWeapon->SetOwner(this);

		m_arrSKillComp.EmplaceAt(0, nullptr);
	}
}

void ATpsCharacter::FocusEnemyOnOff()
{
	if (m_TargetingComp != nullptr)
	{
		m_bTargetingMode = m_TargetingComp->FocusTarget();
	}
}

void ATpsCharacter::FocusEnemySwitch()
{
	if (m_TargetingComp != nullptr)
	{
		m_TargetingComp->SwitchFocusedTarget();
	}
}

float ATpsCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float resultDmg = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	m_CharacterStatComp->ReduceHp(resultDmg);
	return resultDmg;
}

void ATpsCharacter::SetTpsMode()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->SetViewTargetWithBlend(m_TpsChildComponent->GetChildActor(), 0.2);
}

void ATpsCharacter::SetTravelMode()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->SetViewTargetWithBlend(m_TravelChildComponent->GetChildActor(), 0.2);
}

