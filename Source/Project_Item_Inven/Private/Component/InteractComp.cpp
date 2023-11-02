// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InteractComp.h"
#include "GameFramework/Character.h"

#include "Components/SphereComponent.h"


UInteractComp::UInteractComp()
{
}

void UInteractComp::BeginPlay()
{
	Super::BeginPlay();

	m_InteractSphere->OnComponentBeginOverlap.AddDynamic(this, &UInteractComp::OnInteractOverlap);
	m_InteractSphere->OnComponentEndOverlap.AddDynamic(this, &UInteractComp::EndInteractOverlap);
}

void UInteractComp::OnInteractOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_OwnerChar == OtherActor) return;
	m_setInteractableActor.Emplace(OtherActor);
}

void UInteractComp::EndInteractOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	m_setInteractableActor.Remove(OtherActor);
}

