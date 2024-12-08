// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonfire.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Monsters/CharacterControllerComponent/PlayerCharacterController.h"
#include "Project_Monsters/Interfaces/InteractableInterface.h"
#include "Project_Monsters/UserInterface/PlayerHud.h"

ABonfire::ABonfire()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABonfire::Interact_Implementation()
{
	IInteractableInterface::Interact_Implementation();

	if (auto playerCharacter = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		playerCharacter->CreateLevelUpScreen();
	}
}
