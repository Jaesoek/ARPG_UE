
#include "Player/TpsCharacter.h"
#include "Camera/CameraActor.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Component/TargetingComp.h"

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
}

void ATpsCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Default mode
	m_eWeaponMode = EWeaponMode::Default;
	SetTravelMode();

	// Init custom components
	// m_TargetingComp->Init(this);

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

	PlayerInputComponent->BindAction("MouseWheel", IE_Pressed, this, &ATpsCharacter::SwitchWeapon);
	PlayerInputComponent->BindAction("TabKey", IE_Pressed, this, &ATpsCharacter::FocusEnemy);
}

void ATpsCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f)) // float 은 기본적으로 0 비교시 >< 부등호를 사용하지만 변경이 적기 때문에 걍 0.0f ==로 처리
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATpsCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ATpsCharacter::Turn(float NewAxisValue)
{
	if (NewAxisValue != 0.0f)
	{
		AddControllerYawInput(NewAxisValue);
	}
}

void ATpsCharacter::LookUp(float NewAxisValue)
{
	if (NewAxisValue != 0.0f)
	{
		AddControllerPitchInput(NewAxisValue * 0.5f);
	}
}

void ATpsCharacter::SwitchWeapon()
{
	switch (m_eWeaponMode)
	{
	case EWeaponMode::Rifle :
		SetTravelMode();
		SetWeaponMode(EWeaponMode::Default);
		break;
	default:
		SetTpsMode();
		SetWeaponMode(EWeaponMode::Rifle);
		break;
	}
}

void ATpsCharacter::FocusEnemy()
{
	if (m_TargetingComp != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("SetFocus Work!"));
		m_TargetingComp->SetIsFocused(true);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Targeting comp is nullptr!"));
	}
}

void ATpsCharacter::SetTpsMode()
{
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->SetViewTargetWithBlend(m_TpsChildComponent->GetChildActor(), 0.2);
}

void ATpsCharacter::SetTravelMode()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->SetViewTargetWithBlend(m_TravelChildComponent->GetChildActor(), 0.2);
}

