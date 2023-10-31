// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseEnemy.h"
#include "Component/CharacterStatComp.h"
#include "Components/WidgetComponent.h"

#include "Utility/TimerLatent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Decal ���� X
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

	// TOOD: Hp bar widget ��ŷ
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
	// Controller ����
	GetController()->UnPossess();
	GetController()->Destroy();

	// TODO: Dead Animation ��� �� Scheduler Disappear ȿ�� ���
	auto animInstance = GetMesh()->GetAnimInstance();
}

void ABaseEnemy::EnterAttackState()
{
	// TODO: Į �̴� ��� ���, Callback���� ���� ���� ���
	// TODO: Widget ���
	// TODO: Į ����

}
