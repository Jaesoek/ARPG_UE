// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Components/ItemDropComponent.h"

UItemDropComponent::UItemDropComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	m_CurveSizeFloat = CreateDefaultSubobject<UCurveFloat>(TEXT("DropSizeCurve"));
}

void UItemDropComponent::BeginPlay()
{
	Super::BeginPlay();

	setStatus(EItemStatus::Dropping);
}

void UItemDropComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (m_eItemStatus)
	{
		case EItemStatus::Dropping:
		{
			if (m_CurveSizeFloat)
			{
				m_fDropTime += DeltaTime;

				// Size(with Curve), Rotation
				float scaleValue = m_CurveSizeFloat->GetFloatValue(m_fDropTime);
				GetOwner()->SetActorScale3D(FVector(scaleValue));
				GetOwner()->SetActorRelativeRotation(FRotator(m_fDropTime * 360 * 2, 0.f, 0.f));

				// Location
				auto&& location = FMath::Lerp(m_StartPosition, m_DropPosition, m_fDropTime / 2.f);
				location.Z += sinf(m_fDropTime * PI) * 200.f;
				GetOwner()->SetActorLocation(location);
			}
			break;
		}
		case EItemStatus::Dropped:
		{
			break;
		}
	}
}


void UItemDropComponent::setStatus(EItemStatus eStatus)
{
	m_eItemStatus = eStatus;

	if (m_eItemStatus == EItemStatus::Dropped)
	{
		GetOwner()->SetActorRelativeRotation(FRotator::ZeroRotator);

		/*
		m_MeshComponent->SetSimulatePhysics(false);
		m_MeshComponent->SetNotifyRigidBodyCollision(false);
		m_MeshComponent->SetGenerateOverlapEvents(true);
		*/
	}
	else if (m_eItemStatus == EItemStatus::Dropping)
	{
		m_fDropTime = 0.f;
		float nRadius = FMath::RandRange(50, m_uMaxDropRadius);
		float fAngle = (float)FMath::RandRange(0, 359);
		m_StartPosition = GetOwner()->GetActorLocation();
		m_DropPosition = FVector(cos(fAngle), sinf(fAngle), 0.f) * nRadius + m_StartPosition;

		/*
		m_MeshComponent->SetSimulatePhysics(true);
		m_MeshComponent->SetNotifyRigidBodyCollision(true);
		m_MeshComponent->SetGenerateOverlapEvents(false);
		*/
	}
}
