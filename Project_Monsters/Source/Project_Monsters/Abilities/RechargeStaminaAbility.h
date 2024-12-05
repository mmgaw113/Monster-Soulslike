// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RechargeStaminaAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MONSTERS_API URechargeStaminaAbility : public UGameplayAbility
{
	GENERATED_BODY()
	URechargeStaminaAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
