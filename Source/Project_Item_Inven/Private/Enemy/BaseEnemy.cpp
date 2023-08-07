// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseEnemy.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Decal 영향 X
	GetMesh()->bReceivesDecals = false;
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
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
