// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Item_Inven.h"
#include "GameFramework/PlayerState.h"
#include "InGamePlayerState.generated.h"

class ABaseItem;
class AEquipItem;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryEditedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentEditedDelegate);

USTRUCT(BlueprintType)
struct FInventoryStruct
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<ABaseItem> itemClass;
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
	FInventoryEditedDelegate OnInventoryEdited;

	UPROPERTY(BlueprintAssignable, Category = Equipment)
	FEquipmentEditedDelegate OnEquipEdited;

private:
	/** Inventory item array */
	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	TArray<FInventoryStruct> m_arrInventory;

	UPROPERTY(EditAnywhere, Category = Inventory, Meta = (UIMin = 20, UIMax = 60))
	int m_nMaxInventorySize;

	/** Equipment items map */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = true))
	TMap<EEquipType, TSubclassOf<AEquipItem>> m_mapEquipment;
	
public:
	UFUNCTION(BlueprintCallable)
	const TArray<FInventoryStruct>& getInventory() const { return m_arrInventory; };

	UFUNCTION(BlueprintCallable)
	const TMap<EEquipType, TSubclassOf<AEquipItem>>& getEquipment() const { return m_mapEquipment; };


	UFUNCTION(BlueprintCallable)
	bool addItem(TSubclassOf<ABaseItem> itemClass);

	UFUNCTION(BlueprintCallable)
	bool swapItem(int nFirstIndex, int nSecondIndex);

	UFUNCTION(BlueprintCallable)
	bool clearSlot(int inventoryIndex);

	UFUNCTION(BlueprintCallable)
	bool removeItemAt(int inventoryIndex);

private:
	bool addConsumableItem(TSubclassOf<ABaseItem> itemClass);
	bool addEquipableItem(TSubclassOf<ABaseItem> itemClass);

	void MoveToEquip(int inventoryIndex, const AEquipItem& equipItemObj);

	void SwapEquip(int inventoryIndex, EEquipType equipType);

public:
	UFUNCTION(BlueprintCallable)
	bool useItem(int inventoryIndex);

	UFUNCTION(BlueprintCallable)
	bool unEquip(EEquipType eEquipType);
};
