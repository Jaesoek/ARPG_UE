// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

private:
	// 해당 변수 결정 타이밍: 생성시 추가되는 식으로 설정
	//  Defered Spawn 활용 필수
	UPROPERTY()
	TArray<class ABaseItem*> m_arrDropItem;
public:
	FORCEINLINE const TArray<class ABaseItem*>& GetDropItemArr() const { return m_arrDropItem; };
	FORCEINLINE void SetDropItemArr(class ABaseItem* const aItem) { m_arrDropItem.Add(aItem); };

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status, Meta = (AllowPrivateAccess = true))
	class UCharacterStatComp* m_CharacterStatComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UIWidget, Meta = (AllowPrivateAccess = true))
	class UWidgetComponent* m_HpBarWidget;

public:
	ABaseEnemy();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Dead();
};
