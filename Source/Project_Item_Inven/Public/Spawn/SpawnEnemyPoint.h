// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnEnemyPoint.generated.h"

UCLASS(Abstract, BlueprintAble)
class PROJECT_ITEM_INVEN_API ASpawnEnemyPoint : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Editor Mesh")
	class USkeletalMeshComponent* EditorMeshComponent;

public:	
	ASpawnEnemyPoint();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetRotate(const FRotator& rotate);

public:
	UFUNCTION()
	void SpawnMonster();

	UFUNCTION()
	bool IsMonsterSpawned() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class ABaseEnemy> m_classMonster;

	class ABaseEnemy* m_pMyMonster; // UPROPERTY 굳이 설정 하지마 나만 쓸거니까

protected: // Owner 가 없을때 사용
	FTimerHandle m_SpawnTimerHandle;

	UPROPERTY(EditAnywhere, Category = SpawnTime)
	float m_fSpawnDelay;
};
