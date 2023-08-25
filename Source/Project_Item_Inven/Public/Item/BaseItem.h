// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None, Consumable, Equipable
};

UCLASS(Abstract, BlueprintAble)
class PROJECT_ITEM_INVEN_API ABaseItem : public AActor
{
	GENERATED_BODY()

public:
	ABaseItem();

protected:
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemMesh, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* m_MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemMesh, Meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* m_SK_MeshComponent;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemThumbnail, Meta = (AllowPrivateAccess = true))
	UTexture2D* m_Thumbnail;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo, Meta = (AllowPrivateAccess = true))
	EItemType m_eItemType;
public:
	FORCEINLINE EItemType GetItemType() const { return m_eItemType; };

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo, Meta = (AllowPrivateAccess = true))
	FText m_TextItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo, Meta = (AllowPrivateAccess = true))
	FText m_TextItemDescription;

private: // Inventory slot 에 들어갈 수 있는 최대 개수
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo, Meta = (AllowPrivateAccess = true))
	int m_nMaxItemCount;
public:
	FORCEINLINE int GetMaxItemCount() const { return m_nMaxItemCount; };

public: // Item 사용
	UFUNCTION(BlueprintNativeEvent)
	void UseItem();
	virtual void UseItem_Implementation();

public:
	UFUNCTION()
	void SetFocused(bool isFocused);

	/** It contains SetFocused logic */
	UFUNCTION()
	void Interact(const class AProject_Item_InvenCharacter* character);


private:  // Drop Animation 관련 기능
	enum class EItemStatus
	{
		None, Dropping, Dropped
	};

	EItemStatus m_eItemStatus;
	void setStatus(EItemStatus eStatus);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = DropAnimation, Meta = (AllowPrivateAccess = true))
	class UCurveFloat* m_CurveSizeFloat;

	UPROPERTY(EditAnywhere, Category = DropAnimation, Meta = (AllowPrivateAccess = true, UIMin = 50, UIMax = 1000))
	unsigned int m_uMaxDropRadius;

	float m_fDropTime;

	FVector m_StartPosition;
	FVector m_DropPosition;

private: // 습득 FX
	UPROPERTY(EditAnywhere, Category = InteractionEffect, Meta = (AllowPrivateAccess = true))
	class UParticleSystem* m_EffectInteraction;

};
