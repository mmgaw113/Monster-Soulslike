// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TheHuntGameInstance.generated.h"

USTRUCT(Blueprintable)
struct FPlayerAttributes
{
	GENERATED_BODY()

	int Level;
	int CurrentHealth;
	int MaxHealth = 300;
	int CurrentStamina;
	int MaxStamina = 200;
	int Vigor;
	int Endurance;
	int Strength;
	int Dexterity;
	int BloodLust;
	int Arcane;
};

UCLASS()
class PROJECT_MONSTERS_API UTheHuntGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FPlayerAttributes PlayerAttributes;
};
