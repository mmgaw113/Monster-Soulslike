// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpAbility.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Project_Monsters/CharacterControllerComponent/PlayerCharacterController.h"

void UJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	auto character = Cast<APlayerCharacterController>(GetActorInfo().OwnerActor);
	character->ACharacter::Jump();
	K2_CommitAbility();
	//ApplyGameplayEffectToOwner();
}
