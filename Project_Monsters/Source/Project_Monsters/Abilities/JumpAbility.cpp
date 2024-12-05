// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpAbility.h"
#include "Project_Monsters/GameplayEffects/JumpEffect.h"

UJumpAbility::UJumpAbility()
{
	FGameplayTagContainer gameplayTags;
	gameplayTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Player.Action.Stamina.Jump")));
	SetAssetTags(gameplayTags);
	CostGameplayEffectClass = UJumpEffect::StaticClass();
}

void UJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CommitAbility(Handle, ActorInfo, ActivationInfo);
}
