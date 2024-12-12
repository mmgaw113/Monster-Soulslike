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
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMesh* pistolMesh = LoadObject<USkeletalMesh>(
		nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/3DModels/hunter-pistol/source/HunterPistol.HunterPistol'"));
};
