// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_MonstersGameMode.h"
#include "Project_MonstersCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_MonstersGameMode::AProject_MonstersGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
