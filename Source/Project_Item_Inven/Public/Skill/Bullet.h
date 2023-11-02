
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS(Abstract)
class PROJECT_ITEM_INVEN_API ABullet : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly)
	class UStaticMeshComponent* m_Mesh;

	UPROPERTY(EditInstanceOnly)
	class USphereComponent* m_Collider;

	UPROPERTY(EditInstanceOnly)
	class UProjectileMovementComponent* m_ProjMove;

	UPROPERTY(EditInstanceOnly, Category = "Status", Meta = (ClampMin = "1.0", UIMin = "1.0"))
	float m_fDamage;


public:	
	ABullet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Fire(const FVector& direction);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
