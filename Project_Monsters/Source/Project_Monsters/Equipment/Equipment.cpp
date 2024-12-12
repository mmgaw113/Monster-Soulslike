// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"

#include "Kismet/GameplayStatics.h"
#include "Project_Monsters/CharacterControllerComponent/BaseCharacterController.h"

AEquipment::AEquipment()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEquipment::UpdateDamage()
{
	auto characterController = Cast<ABaseCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	damage = 0;
	damage += characterController->CalculateArcaneOutput(Arcane) + characterController->CalculateDexterityOutput(Dexterity) + characterController->CalculateStrengthOutput(Strength);
}
