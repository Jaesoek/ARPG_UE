
#include "Skill/Bullet.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ABullet::ABullet()
{
	// About Components
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Bullet"));
	m_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider Bullet"));
	m_ProjMove = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjMovement Bullet"));

	RootComponent = m_Collider;
	m_Mesh->SetupAttachment(m_Collider);

	m_ProjMove->SetUpdatedComponent(m_Collider);


	// About Actor
	InitialLifeSpan = 5.f;


	PrimaryActorTick.bCanEverTick = true;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::Fire(const FVector& direction)
{
	m_ProjMove->Velocity = direction * m_ProjMove->InitialSpeed;
}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// TODO: Damage 입을수 있는 물체에 대해서는 데미지 입력
	// TODO: 기타 Physics에 대해서는 Impulse 입력
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(m_ProjMove->Velocity * 100.0f, Hit.ImpactPoint);
	}

	Destroy();
}
