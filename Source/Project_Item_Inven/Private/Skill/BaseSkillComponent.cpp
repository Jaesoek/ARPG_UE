// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/BaseSkillComponent.h"

UBaseSkillComponent::UBaseSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UBaseSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UBaseSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

