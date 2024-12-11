// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"

AEquipment::AEquipment()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEquipment::BeginPlay()
{
	Super::BeginPlay();
}

void AEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
