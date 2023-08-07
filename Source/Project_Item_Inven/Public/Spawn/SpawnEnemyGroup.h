// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnEnemyGroup.generated.h"

UCLASS()
class PROJECT_ITEM_INVEN_API ASpawnEnemyGroup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnEnemyGroup();

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnPoints, Meta = (AllowPrivateAccess = true))
	TArray<class ASpawnEnemyPoint*> m_arrSpawnPoints;

public:
	UFUNCTION()
	void SpawnMonsters();

protected: // Net owner 가 없으니 시간 기준으로 설정
	FTimerHandle m_SpawnTimerHandle;

	UPROPERTY(EditAnywhere, Category = SpawnTime)
	float m_fSpawnDelay;
};
