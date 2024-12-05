// Fill out your copyright notice in the Description page of Project Settings.


#include "RechargeStaminaAbility.h"
#include "Project_Monsters/GameplayEffects/RechargeStaminaEffect.h"

URechargeStaminaAbility::URechargeStaminaAbility()
{
	FGameplayTagContainer gameplayTags;
	gameplayTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Player.Action.Stamina.Increase")));
	SetAssetTags(gameplayTags);
	CostGameplayEffectClass = URechargeStaminaEffect::StaticClass();
}

void URechargeStaminaAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CommitAbility(Handle, ActorInfo, ActivationInfo);
}
