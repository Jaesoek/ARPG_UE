// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseEnemy.h"

#include "UI/EnemyHpWidget.h"

#include "Component/CharacterStatComp.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"

#include "Utility/TimerLatent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Decal 영향 X
	GetMesh()->bReceivesDecals = false;

	// Hp Widget component
	m_HpBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBarWidgetComp"));
	m_HpBarWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_HpBarWidgetComp->SetRelativeLocation(FVector::ZeroVector);
}

void ABaseEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto meshMaterial = GetMesh()->GetMaterial(0);
	m_MID_Mesh = UMaterialInstanceDynamic::Create(meshMaterial, this);
	GetMesh()->SetMaterial(0, m_MID_Mesh);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	m_enemyHpBar = Cast<UEnemyHpWidget>(m_HpBarWidgetComp->GetWidget());
	m_CharacterStatComp = Cast<UCharacterStatComp>(GetComponentByClass(UCharacterStatComp::StaticClass()));
	if (IsValid(m_CharacterStatComp))
		m_CharacterStatComp->OnHpChanged().AddUObject(this, &ABaseEnemy::EditHpProgress);

	SpawnStart();
}

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	m_CharacterStatComp->ReduceHp(DamageAmount);
	return DamageAmount;
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

void ABaseEnemy::EditHpProgress(float currentHp, bool isHeal)
{
	float percent = currentHp / m_CharacterStatComp->GetMaxHp();
	if (IsValid(m_enemyHpBar))
		m_enemyHpBar->progress_hp->SetPercent(percent);
}

void ABaseEnemy::EnterAttackState()
{
	// TODO: 칼 뽑는 모션 출력, Callback으로 다음 내용 출력
	// TODO: Widget 출력
	// TODO: 칼 장착

}
