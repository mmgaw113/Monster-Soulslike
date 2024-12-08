// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "Sickle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MONSTERS_API ASickle : public AEquipment
{
	GENERATED_BODY()

public:
	ASickle();

	USkeletalMesh* sickleMesh = LoadObject<USkeletalMesh>(
		nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/Weapon_Pack/Skeletal_Mesh/SK_Sickle.SK_Sickle'"));
};
