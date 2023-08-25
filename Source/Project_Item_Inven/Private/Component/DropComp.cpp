// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DropComp.h"

UDropComp::UDropComp()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UDropComp::PostLoad()
{
	// Init owner Actor
	m_ActorOwner = GetOwner();


}

void UDropComp::BeginPlay()
{
	Super::BeginPlay();

}

void UDropComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

