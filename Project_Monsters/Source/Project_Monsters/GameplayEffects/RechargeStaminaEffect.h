// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "RechargeStaminaEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MONSTERS_API URechargeStaminaEffect : public UGameplayEffect
{
	GENERATED_BODY()
	URechargeStaminaEffect();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	FGameplayModifierInfo EffectInfo;
};
