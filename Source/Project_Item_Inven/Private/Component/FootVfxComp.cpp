// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/FootVfxComp.h"

#include "Components/SphereComponent.h"

UFootVfxComp::UFootVfxComp()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Targeting Setting
	FootStepSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TargetingSphere"));
	FootStepSphere->SetupAttachment(this);
	FootStepSphere->InitSphereRadius(40.f);

	// Set Targeting
	FootStepSphere->SetCollisionObjectType(ECC_Pawn);
	FootStepSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	FootStepSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	FootStepSphere->SetGenerateOverlapEvents(true);

	FootStepSphere->OnComponentBeginOverlap.AddDynamic(this, &UFootVfxComp::OnTargetingOverlap);
	FootStepSphere->OnComponentEndOverlap.AddDynamic(this, &UFootVfxComp::EndTargetingOverlap);
}


void UFootVfxComp::BeginPlay()
{
	Super::BeginPlay();

}


void UFootVfxComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UFootVfxComp::OnTargetingOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("Foot Begin Overlap"));
}

void UFootVfxComp::EndTargetingOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("Foot End Overlap"));
}

UNiagaraSystem* UFootVfxComp::GetFootVfx()
{
	return m_FootVfx;
}

USoundBase* UFootVfxComp::GetFootSound()
{
	return m_FootSound;
}

