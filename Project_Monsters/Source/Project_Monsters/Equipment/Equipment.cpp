// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"

#include "Kismet/GameplayStatics.h"
#include "Project_Monsters/CharacterControllerComponent/BaseCharacterController.h"

AEquipment::AEquipment()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEquipment::BeginPlay()
{
	Super::BeginPlay();
	auto characterController = Cast<ABaseCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	damage += characterController->CalculateDamageOutput(Strength, Dexterity, Arcane);
}

void AEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
