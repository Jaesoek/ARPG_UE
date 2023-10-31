// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseEnemy.h"
#include "Component/CharacterStatComp.h"
#include "Components/WidgetComponent.h"

#include "Utility/TimerLatent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Decal 영향 X
	GetMesh()->bReceivesDecals = false;

	// Status component
	m_CharacterStatComp = CreateDefaultSubobject<UCharacterStatComp>(TEXT("StatusComponent"));

	// Hp Widget component
	m_HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBarWidgetComp"));
	m_HpBarWidget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_HpBarWidget->SetRelativeLocation(FVector::ZeroVector);
}

void ABaseEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto meshMaterial = GetMesh()->GetMaterial(0);
	m_MID_Mesh = UMaterialInstanceDynamic::Create(meshMaterial, this);
	GetMesh()->SetMaterial(0, m_MID_Mesh);

	// TOOD: Hp bar widget 링킹
	//m_CharacterStatComp->OnHpChanged().AddUObject(this, );
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	SpawnStart();
}

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void ABaseEnemy::SpawnStart()
{
	m_MID_Mesh->SetScalarParameterValue(TEXT("erode"), 0.f);

	GetWorld()->GetLatentActionManager().AddNewAction(
		this, GetUniqueID(),
		new TimerLatent(
			[&]() -> bool { // Update
				float fProgress;
				m_MID_Mesh->GetScalarParameterValue(TEXT("erode"), fProgress);
				fProgress += GetWorld()->DeltaTimeSeconds * 0.6f;
				m_MID_Mesh->SetScalarParameterValue(TEXT("erode"), fProgress);

				return fProgress > 1.f;
			},
			[&]() { // Complete
				 auto aiController = GetWorld()->SpawnActor<AController>(AIControllerClass);
				 aiController->Possess(this);
			})
	);
}

void ABaseEnemy::Dead()
{
	// Controller 제거
	GetController()->UnPossess();
	GetController()->Destroy();

	// TODO: Dead Animation 출력 및 Scheduler Disappear 효과 출력
	auto animInstance = GetMesh()->GetAnimInstance();
}

void ABaseEnemy::EnterAttackState()
{
	// TODO: 칼 뽑는 모션 출력, Callback으로 다음 내용 출력
	// TODO: Widget 출력
	// TODO: 칼 장착

}
