// Fill out your copyright notice in the Description page of Project Settings.


#include "TheHuntGameMode.h"
#include "UObject/ConstructorHelpers.h"

ATheHuntGameMode::ATheHuntGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/PlayerController/bp_PlayerCharacterController"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
