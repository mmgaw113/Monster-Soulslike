// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility_Montage.h"
#include "JumpAttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MONSTERS_API UJumpAttackAbility : public UGameplayAbility_Montage
{
	GENERATED_BODY()

	UJumpAttackAbility();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
