// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpAbility.h"

#include "Project_Monsters/CharacterControllerComponent/PlayerCharacterController.h"

void UJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FGameplayTag JumpTag = FGameplayTag::RequestGameplayTag(FName("Player.Action.Jump"));
	AbilityTags.AddTag(JumpTag);
	auto character = Cast<APlayerCharacterController>(GetActorInfo().OwnerActor);
	//Cast<ACharacter>(character->GetCharacterMovement())->ACharacter::Jump();
	K2_CommitAbility();
	//ApplyGameplayEffectToOwner();
}
