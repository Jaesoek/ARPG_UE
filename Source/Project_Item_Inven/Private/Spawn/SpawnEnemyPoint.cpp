// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawn/SpawnEnemyPoint.h"
#include "Enemy/BaseEnemy.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"

ASpawnEnemyPoint::ASpawnEnemyPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	

	EditorMeshComponent = CreateEditorOnlyDefaultSubobject<USkeletalMeshComponent>(TEXT("Editor Mesh"));

	EditorMeshComponent->SetupAttachment(RootComponent);

	m_fSpawnDelay = 5.f;
}

void ASpawnEnemyPoint::BeginPlay()
{
	Super::BeginPlay();

	auto enemy = Cast<ABaseEnemy>(m_classMonster.GetDefaultObject());
	enemy->GetMesh();


	// Owner가 없으면
	if (GetOwner() == nullptr)
	{
		GetWorldTimerManager().SetTimer(
			m_SpawnTimerHandle, this, &ASpawnEnemyPoint::SpawnMonster, m_fSpawnDelay, true
		);
	}
}

void ASpawnEnemyPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnEnemyPoint::SetRotate(const FRotator& rotate)
{
	SetActorRotation(rotate);
}

bool ASpawnEnemyPoint::IsMonsterSpawned() const
{
	return IsValid(m_pMyMonster);
}

void ASpawnEnemyPoint::SpawnMonster()
{
	if (!IsMonsterSpawned())
	{
		m_pMyMonster = GetWorld()->SpawnActor<ABaseEnemy>(
			m_classMonster, GetActorLocation(), GetActorRotation()
		);
	}
}

