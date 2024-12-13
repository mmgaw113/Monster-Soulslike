// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpAttackAbility.h"

UJumpAttackAbility::UJumpAttackAbility()
{
	MontageToPlay = LoadObject<UAnimMontage>(nullptr, TEXT("/Script/Engine.AnimMontage'/Game/Animations/Attacks/AM_JumpAttack.AM_JumpAttack'"));
}

void UJumpAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CommitAbility(Handle, ActorInfo, ActivationInfo);
}
