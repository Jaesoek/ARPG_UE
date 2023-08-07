// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawn/SpawnEnemyGroup.h"
#include "Spawn/SpawnEnemyPoint.h"

ASpawnEnemyGroup::ASpawnEnemyGroup()
{
	PrimaryActorTick.bCanEverTick = true;

	m_fSpawnDelay = 2.f;
}

void ASpawnEnemyGroup::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		m_SpawnTimerHandle, this, &ASpawnEnemyGroup::SpawnMonsters, m_fSpawnDelay, true
	);
}

void ASpawnEnemyGroup::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	for (const auto spawnPoint : m_arrSpawnPoints)
	{
		spawnPoint->SetOwner(this);
		spawnPoint->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		spawnPoint->SetRotate(GetActorRotation());
	}
}

void ASpawnEnemyGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnEnemyGroup::SpawnMonsters()
{
	for (const auto spawnPoint : m_arrSpawnPoints)
	{
		spawnPoint->SpawnMonster();
	}
}

