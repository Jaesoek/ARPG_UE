// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseEnemy.h"
#include "Component/CharacterStatComp.h"
#include "Components/WidgetComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Decal 영향 X
	GetMesh()->bReceivesDecals = false;

	// Status component
	m_CharacterStatComp = CreateDefaultSubobject<UCharacterStatComp>(TEXT("StatusComponent"));

	// Hp Widget component
	m_HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBarWidgetComp"));
	m_HpBarWidget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_HpBarWidget->SetRelativeLocation(FVector::ZeroVector);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

//	m_CharacterStatComp->OnHpChanged().AddUObject(this, );
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseEnemy::Dead()
{
	// Animation 돌리고 
	auto animInstance = GetMesh()->GetAnimInstance();
}
