// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equipment.generated.h"

UENUM(BlueprintType)
enum EScaling
{
	None,
	S,
	A,
	B,
	C,
	D,
	E
};

UCLASS()
class PROJECT_MONSTERS_API AEquipment : public AActor
{
	GENERATED_BODY()

public:
	AEquipment();
	void UpdateDamage();

	USkeletalMeshComponent* mesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int damage;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TEnumAsByte<EScaling> Arcane;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TEnumAsByte<EScaling> Dexterity;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TEnumAsByte<EScaling> Strength;
};
