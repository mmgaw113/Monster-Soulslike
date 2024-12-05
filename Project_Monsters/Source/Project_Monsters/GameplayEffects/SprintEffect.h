// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "SprintEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MONSTERS_API USprintEffect : public UGameplayEffect
{
	GENERATED_BODY()

	USprintEffect();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	FGameplayModifierInfo EffectInfo;
};
