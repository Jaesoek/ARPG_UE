// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_Item_Inven.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"


UCLASS(Abstract, BlueprintAble)
class PROJECT_ITEM_INVEN_API ABaseItem : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemMesh, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* m_MeshComponent;

	UPROPERTY(EditAnywhere, Category = DropAnimation)
	class UItemDropComponent* m_ItemDropComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo, Meta = (AllowPrivateAccess = true))
	UTexture2D* m_Thumbnail;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemInfo, Meta = (AllowPrivateAccess = true))
	EItemType m_eItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo, Meta = (AllowPrivateAccess = true))
	FText m_TextItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo, Meta = (AllowPrivateAccess = true))
	FText m_TextItemDescription;

private:
	UPROPERTY(EditAnywhere, Category = "Interaction", Meta = (AllowPrivateAccess = true))
	class UParticleSystem* m_EffectInteraction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo, Meta = (AllowPrivateAccess = true))
	int m_nMaxItemCount;

public:
	FORCEINLINE int GetMaxItemCount() const { return m_nMaxItemCount; };

public:
	ABaseItem();

protected:
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void SetFocused(bool isFocused);

	UFUNCTION()
	bool Interact(const class ACharacter* character, FString& strUnableReason);

public:
	FORCEINLINE UTexture2D* GetItemThumbnail() const { return m_Thumbnail; };
	FORCEINLINE EItemType GetItemType() const { return m_eItemType; };
	FORCEINLINE FText GetItemName() const { return m_TextItemName; };
	FORCEINLINE FText GetItemDescription() const { return m_TextItemDescription; };

public:
	virtual bool UseItem(ACharacter* character);

	UFUNCTION(BlueprintCallable)
	bool UseItemBP(ACharacter* character);
};
