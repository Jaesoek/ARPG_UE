// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	class UCharacterStatComp* m_CharacterStatComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIWidget)
	class UWidgetComponent* m_HpBarWidgetComp;

	class UEnemyHpWidget* m_enemyHpBar;

	class UMaterialInstanceDynamic* m_MID_Mesh;

private:
	// 해당 변수 결정 타이밍: 생성시 추가되는 식으로 설정
	//  Defered Spawn 활용 필수
	UPROPERTY()
	TArray<class ABaseItem*> m_arrDropItem;

public:
	ABaseEnemy();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	void SpawnStart();

	void Dead();

	void EditHpProgress(float currentHp, bool isHeal);

public:
	UFUNCTION(BlueprintCallable)
	void EnterAttackState();

public:
	FORCEINLINE const TArray<class ABaseItem*>& GetDropItemArr() const { return m_arrDropItem; };
	FORCEINLINE void SetDropItemArr(class ABaseItem* const aItem) { m_arrDropItem.Add(aItem); };
};
