// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/Project_Item_InvenCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Item/BaseItem.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Enemy/BaseEnemy.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// AProject_Item_InvenCharacter

AProject_Item_InvenCharacter::AProject_Item_InvenCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Mesh Decal 영향 X
	GetMesh()->bReceivesDecals = false;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create sphereComponet for interaction
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->InitSphereRadius(120.f);

	// Create sphereComponet for enemy focusing
	TargetingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("EnemyTargetingSphere"));
	TargetingSphere->SetupAttachment(RootComponent);
	TargetingSphere->InitSphereRadius(2000.f);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProject_Item_InvenCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
//	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &AProject_Item_InvenCharacter::AttackHard);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProject_Item_InvenCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProject_Item_InvenCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AProject_Item_InvenCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AProject_Item_InvenCharacter::LookUp);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AProject_Item_InvenCharacter::Interaction);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AProject_Item_InvenCharacter::RangeSkillStart);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AProject_Item_InvenCharacter::RangeSkillFire);
	//	PlayerInputComponent->BindAction("Attack_Hard", IE_Pressed, this, &AProject_Item_InvenCharacter::AttackHard);
//	PlayerInputComponent->BindAction("FocusEnemy", IE_Pressed, this, &AProject_Item_InvenCharacter::TargetingEnemy);
}

void AProject_Item_InvenCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AProject_Item_InvenCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Interaction
	InteractionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	InteractionSphere->SetGenerateOverlapEvents(true);

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AProject_Item_InvenCharacter::OnInteractionOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AProject_Item_InvenCharacter::EndInteractionOverlap);

	// Enemy focus
	TargetingSphere->SetCollisionObjectType(ECC_WorldDynamic);
	TargetingSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TargetingSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	TargetingSphere->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	TargetingSphere->SetGenerateOverlapEvents(true);

	TargetingSphere->OnComponentBeginOverlap.AddDynamic(this, &AProject_Item_InvenCharacter::OnTargetingOverlap);
	TargetingSphere->OnComponentEndOverlap.AddDynamic(this, &AProject_Item_InvenCharacter::EndTargetingOverlap);

	// Init MIDs for range skill far
	if (M_RangeCheck != nullptr)
	{
		MID_RangeCheck = UMaterialInstanceDynamic::Create(M_RangeCheck, this);
		if (MID_RangeCheck == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Your Message"));
		}
	}
}

void AProject_Item_InvenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProject_Item_InvenCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AProject_Item_InvenCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AProject_Item_InvenCharacter::Turn(float NewAxisValue)
{
	if (NewAxisValue != 0.f)
	{
		AddControllerYawInput(NewAxisValue);
		OnMouseTurn.Broadcast();
	}
}

void AProject_Item_InvenCharacter::LookUp(float NewAxisValue)
{
	if (NewAxisValue != 0.f)
	{
		AddControllerPitchInput(NewAxisValue * 0.5f);
		OnMouseTurn.Broadcast();
	}
}

void AProject_Item_InvenCharacter::Interaction()
{
	if (!InteractiveActor) return;

	ABaseItem* item = Cast<ABaseItem>(InteractiveActor);
//	item->Interact(this);

	ptrInteractionIndicator->RemoveFromParent();
	InteractiveActor = nullptr;
}

void AProject_Item_InvenCharacter::OnInteractionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!InteractiveActor)
	{
		auto interactionItem = Cast<ABaseItem>(OtherActor);
		if (interactionItem != nullptr)
		{
			InteractiveActor = OtherActor;

			ptrInteractionIndicator = Cast<UUserWidget>(CreateWidget(GetWorld(), Interaction_Class));

			FVector2D pos2DIndicator;
			UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
				GetWorld()->GetFirstPlayerController(),
				OtherActor->GetActorLocation(),
				pos2DIndicator,
				true
			);
			Cast<UCanvasPanelSlot>(ptrInteractionIndicator->GetWidgetFromName(TEXT("BoxIndicator"))->Slot)
				->SetPosition(pos2DIndicator);
			ptrInteractionIndicator->AddToViewport();
			interactionItem->SetFocused(true);
		}
	}
}

void AProject_Item_InvenCharacter::EndInteractionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (InteractiveActor == OtherActor)
	{
		auto interactionItem = Cast<ABaseItem>(OtherActor);
		if (interactionItem != nullptr)
		{
			ptrInteractionIndicator->RemoveFromParent();
			interactionItem->SetFocused(false);

			InteractiveActor = nullptr;
		}
	}
}

void AProject_Item_InvenCharacter::OnTargetingOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bool isAlready{};
	m_setTargetable.Add(Cast<ABaseEnemy>(OtherActor), &isAlready);
}

void AProject_Item_InvenCharacter::EndTargetingOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (m_pTargetedEnemy == OtherActor)
		m_pTargetedEnemy = nullptr;

	m_setTargetable.Remove(Cast<ABaseEnemy>(OtherActor));
}

void AProject_Item_InvenCharacter::TargetingEnemy()
{
	float distance = MAX_flt;
	for (auto& enemy : m_setTargetable)
	{
		float tempDistance = FVector::Dist(enemy->GetActorLocation(), GetActorLocation());
		if (tempDistance < distance)
		{
			distance = tempDistance;
			m_pTargetedEnemy = enemy;
		}
	}

	/* 추후 추가
	if (m_pTargetedEnemy != nullptr)
		m_pTargetedEnemy->ReleaseTargeting();
	m_pTargetedEnemy->SetTargeting();
	*/
}

void AProject_Item_InvenCharacter::RangeSkillStart()
{
	// Spawn actor in here
	check(MID_RangeCheck);

	auto animInstance = GetMesh()->GetAnimInstance();
	animInstance->Montage_Play(m_Montage, 1.f);

	auto IgnoreOwner = FCollisionQueryParams::DefaultQueryParam;
	IgnoreOwner.AddIgnoredActor(this);

	auto cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FHitResult result;
	bool isHit = GetWorld()->LineTraceSingleByObjectType(
		result,
		cameraManager->GetCameraLocation(),
		cameraManager->GetCameraLocation() + cameraManager->GetActorForwardVector() * 10000,
		ECollisionChannel::ECC_WorldStatic,
		IgnoreOwner
	);

	FVector location;
	if (isHit)
		location = result.ImpactPoint;
	else
		location = GetActorLocation();

	CheckRangeDecalActor = GetWorld()->SpawnActor<ADecalActor>(location, FRotator());
	if (CheckRangeDecalActor)
	{
		CheckRangeDecalActor->SetDecalMaterial(MID_RangeCheck);
		CheckRangeDecalActor->GetDecal()->DecalSize = FVector(600.0f, 600.0f, 600.0f);
	}

	OnMouseTurn.AddUObject(this, &AProject_Item_InvenCharacter::RangeSkillCasting);
}

void AProject_Item_InvenCharacter::RangeSkillCasting()
{
	if (CheckRangeDecalActor != nullptr)
	{
		auto IgnoreOwner = FCollisionQueryParams::DefaultQueryParam;
		IgnoreOwner.AddIgnoredActor(this);

		auto cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		FHitResult result;
		bool isHit = GetWorld()->LineTraceSingleByObjectType(
			result,
			cameraManager->GetCameraLocation(),
			cameraManager->GetCameraLocation() + cameraManager->GetActorForwardVector() * 4000,
			ECollisionChannel::ECC_WorldStatic,
			IgnoreOwner
		);

		bool isAvailable = true;

		FVector location;
		FRotator pitchRotation = FRotator{ -90.f, 0.f, 0.f };
		if (isHit)
		{ // 사정거리 내부
			location = result.ImpactPoint;
			pitchRotation = FRotationMatrix::MakeFromX(result.ImpactNormal).Rotator();

			if (FVector::DotProduct(FVector::ZAxisVector, result.ImpactNormal) < 0.4f)
				isAvailable = false;
		}
		else
		{ // 사정거리 바깥
			isAvailable = false;
			location = GetActorLocation();
		}

		CheckRangeDecalActor->SetActorLocation(location);
		CheckRangeDecalActor->SetActorRotation(pitchRotation);
		if (isAvailable)
			MID_RangeCheck->SetScalarParameterValue(FName(TEXT("IsAvailable")), 1.f);
		else
			MID_RangeCheck->SetScalarParameterValue(FName(TEXT("IsAvailable")), 0.f);
	}
}

void AProject_Item_InvenCharacter::RangeSkillFire()
{
	// Spawn actor in there
	check(CheckRangeDecalActor);

	auto animInstance = GetMesh()->GetAnimInstance();
	animInstance->Montage_JumpToSection(TEXT("Attack"), m_Montage);

	CheckRangeDecalActor->Destroy();
}
