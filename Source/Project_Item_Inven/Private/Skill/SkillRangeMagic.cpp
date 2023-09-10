// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillRangeMagic.h"
#include "Player/TpsCharacter.h"
#include "Component/CharacterStatComp.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"


void USkillRangeMagic::BeginPlay()
{
	Super::BeginPlay();

	m_MID_RangeCheck = UMaterialInstanceDynamic::Create(m_M_RangeCheck, this);

	m_isCasting = false;
}

void USkillRangeMagic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_isCasting)
	{
		if (m_fMaxCoolTime > m_fCoolTime)
		{
			if (m_fMaxCoolTime <= m_fCoolTime + DeltaTime)
				SetCoolTime(m_fMaxCoolTime);
			else
				SetCoolTime(m_fCoolTime + DeltaTime);
		}
	}
}


bool USkillRangeMagic::ActivateSkill(FString& strUnableReason)
{
	if (m_fMaxCoolTime > m_fCoolTime)
	{
		strUnableReason += FString(TEXT("Cool time issue!"));
		return false;
	}
	else if (m_OwnerCharcter->GetCharacterStat()->GetHp() < m_fSkillCost)
	{
		strUnableReason += FString(TEXT("Not enough HP"));
		return false;
	}

	m_isCasting = true;
	SetCoolTime(0.f);

	m_OwnerCharcter->SetTpsMode();
	m_OwnerCharcter->PlayAnimMontage(m_AnimMontage);
	m_OwnerCharcter->GetCharacterStat()->ReduceHp(m_fSkillCost);

	auto IgnoreOwner = FCollisionQueryParams::DefaultQueryParam;
	IgnoreOwner.AddIgnoredActor(m_OwnerCharcter);

	auto cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FHitResult result{};
	bool isHit = GetWorld()->LineTraceSingleByObjectType(
		result,
		cameraManager->GetCameraLocation(),
		cameraManager->GetCameraLocation() + cameraManager->GetActorForwardVector() * 10000,
		ECollisionChannel::ECC_WorldStatic,
		IgnoreOwner
	);

	FVector location = m_OwnerCharcter->GetActorLocation();
	if (isHit)
		location = result.ImpactPoint;

	m_DA_RangeCheck = GetWorld()->SpawnActor<ADecalActor>(location, FRotator());
	if (m_DA_RangeCheck)
	{
		m_DA_RangeCheck->SetDecalMaterial(m_MID_RangeCheck);
		m_DA_RangeCheck->GetDecal()->DecalSize = FVector(600.0f, 600.0f, 600.0f);
	}

	m_OwnerCharcter->OnCharacterMove.BindUObject(this, &USkillRangeMagic::CastingSkill);
	return true;
}

bool USkillRangeMagic::ReleasedSkill()
{
	if (!m_isCasting)
		return false;

	auto location = m_DA_RangeCheck->GetActorLocation();
	m_DA_RangeCheck->Destroy();

	m_OwnerCharcter->OnCharacterMove.Unbind();
	m_OwnerCharcter->SetTravelMode();
	m_isCasting = false;

	m_OwnerCharcter->PlayAnimMontage(m_AnimMontage,1.0f, FName(TEXT("Attack")));
	return true;
}

void USkillRangeMagic::CastingSkill()
{
	if (!IsValid(m_DA_RangeCheck)) return;

	auto IgnoreOwner = FCollisionQueryParams::DefaultQueryParam;
	IgnoreOwner.AddIgnoredActor(m_OwnerCharcter);

	auto cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FHitResult result;
	bool isHit = GetWorld()->LineTraceSingleByObjectType(
		result,
		cameraManager->GetCameraLocation(),
		cameraManager->GetCameraLocation() + cameraManager->GetActorForwardVector() * 4000,
		ECollisionChannel::ECC_WorldStatic,
		IgnoreOwner
	);

	bool isAvailable = true;
	FVector location;
	FRotator pitchRotation = FRotator{ -90.f, 0.f, 0.f };
	if (isHit)
	{ // 사정거리 내부
		location = result.ImpactPoint;
		pitchRotation = FRotationMatrix::MakeFromX(result.ImpactNormal).Rotator();

		if (FVector::DotProduct(FVector::ZAxisVector, result.ImpactNormal) < 0.4f)
			isAvailable = false;
	}
	else
	{ // 사정거리 바깥
		isAvailable = false;
		location = m_OwnerCharcter->GetActorLocation();
	}

	m_DA_RangeCheck->SetActorLocation(location);
	m_DA_RangeCheck->SetActorRotation(pitchRotation);
	if (isAvailable)
		m_MID_RangeCheck->SetScalarParameterValue(FName(TEXT("IsAvailable")), 1.f);
	else
		m_MID_RangeCheck->SetScalarParameterValue(FName(TEXT("IsAvailable")), 0.f);
}
