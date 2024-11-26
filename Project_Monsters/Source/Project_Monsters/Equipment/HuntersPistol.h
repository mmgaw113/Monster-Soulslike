// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "HuntersPistol.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MONSTERS_API AHuntersPistol : public AEquipment
{
	GENERATED_BODY()

	AHuntersPistol();

	USkeletalMesh* blunderBussMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/3DModels/blunderbuss/source/Blunderbuss1.Blunderbuss1'"));
};
