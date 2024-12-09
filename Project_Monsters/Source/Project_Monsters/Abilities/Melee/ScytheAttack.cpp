// Fill out your copyright notice in the Description page of Project Settings.


#include "ScytheAttack.h"

UScytheAttack::UScytheAttack()
{
	MontageToPlay = LoadObject<UAnimMontage>(nullptr, TEXT("/Script/Engine.AnimMontage'/Game/Animations/MixamoAnimations/Animations/MM_sword_and_shield_attack__2__Montage.MM_sword_and_shield_attack__2__Montage'"));
}

void UScytheAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CommitAbility(Handle, ActorInfo, ActivationInfo);
}
