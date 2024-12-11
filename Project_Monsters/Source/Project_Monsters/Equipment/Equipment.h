// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equipment.generated.h"

UENUM(BlueprintType)
enum EScaling
{
	S,
	A,
	B,
	C,
	E
};

UCLASS()
class PROJECT_MONSTERS_API AEquipment : public AActor
{
	GENERATED_BODY()

public:
	AEquipment();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	USkeletalMeshComponent* mesh;
	
	UPROPERTY()
	TEnumAsByte<EScaling> Arcane;
	UPROPERTY()
	TEnumAsByte<EScaling> Dexterity;
	UPROPERTY()
	TEnumAsByte<EScaling> Strength;
};
