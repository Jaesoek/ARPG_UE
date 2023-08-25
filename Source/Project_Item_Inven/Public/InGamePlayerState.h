// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "InGamePlayerState.generated.h"

class ABaseItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAddItemDelegate);

USTRUCT(BlueprintType)
struct FInventoryStruct
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UClass* itemClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	FText name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	FText description;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UTexture2D* texture;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int count;
};

UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API AInGamePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FAddItemDelegate OnAddItem;

private:
	/** Inventory item array */
	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	TArray<FInventoryStruct> m_arrInventory;

	UPROPERTY(EditAnywhere, Category = Inventory, Meta = (UIMin = 5, UIMax = 15))
	int m_nMaxInventorySize;

public:
	const TArray<FInventoryStruct>* getInventory() const { return &m_arrInventory; };

	// Inventory 내용물 추가
	UFUNCTION(BlueprintCallable)
	bool addItem(UClass* itemClass, FText name, FText description, UTexture2D* thumbnail);

	bool addConsumableItem(UClass* itemClass, FText name, FText description, UTexture2D* thumbnail);
	bool addEquipableItem(UClass* itemClass, FText name, FText description, UTexture2D* thumbnail);

	UFUNCTION(BlueprintCallable)
	bool swapItem(int nFirstIndex, int nSecondIndex);

	// Inventory 내용물 삭제
	UFUNCTION(BlueprintCallable)
	bool removeItemAt(int pos);

public:
	UPROPERTY(EditAnywhere, Category = Equip)
	TSubclassOf<class AEquipItem> m_Rifle;

	UPROPERTY(EditAnywhere, Category = Equip)
	TSubclassOf<class AEquipItem> m_Sword;

private:
	/** Equip item map */
	TMap<FString, UClass*> m_mapEquip;

public:
	const TMap<FString, UClass*>* getEquipMap() const { return &m_mapEquip; };

public:
	bool useItem(const FInventoryStruct& itemClass);
private:
	bool useEquipable();
	bool useConsumable();
};
