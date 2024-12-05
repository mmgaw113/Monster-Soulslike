// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintAbility.h"

#include "Project_Monsters/GameplayEffects/SprintEffect.h"

USprintAbility::USprintAbility()
{
	FGameplayTagContainer gameplayTags;
	gameplayTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Player.Action.Stamina.Decrease")));
	SetAssetTags(gameplayTags);
	CostGameplayEffectClass = USprintEffect::StaticClass();
}

void USprintAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CommitAbility(Handle, ActorInfo, ActivationInfo);
}
