// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterController.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffectTypes.h"
#include "Project_Monsters/Abilities/TheHuntAbilitySystemComponent.h"
#include "Project_Monsters/Attributes/TheHuntAttributeSet.h"
#include "Project_Monsters/Equipment/Equipment.h"

ABaseCharacterController::ABaseCharacterController()
{
	abilitySystemComponent = CreateDefaultSubobject<UTheHuntAbilitySystemComponent>(TEXT("Ability System Component"));
	abilitySystemComponent->SetIsReplicated(true);

	attributes = CreateDefaultSubobject<UTheHuntAttributeSet>(TEXT("Attributes"));
	characterLevel = 1;
	vigorLevel = 1;
	enduranceLevel = 1;
	strengthLevel = 1;
	dexterityLevel = 1;
	bloodLustLevel = 1;
	arcaneLevel = 1;
}

void ABaseCharacterController::AddEquipment(FName SocketName, UClass* Equipment) const
{
	FActorSpawnParameters spawnInfo;
	FAttachmentTransformRules transformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;
	auto equipmentItem = GetWorld()->SpawnActor<AEquipment>(Equipment, GetMesh()->GetSocketLocation(SocketName),
		GetMesh()->GetSocketRotation(SocketName), spawnInfo);

	if (equipmentItem)
	{
		equipmentItem->AttachToComponent(GetMesh(), transformRules, SocketName);	
	}
}

UAbilitySystemComponent* ABaseCharacterController::GetAbilitySystemComponent() const
{
	return abilitySystemComponent;
}

void ABaseCharacterController::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!abilitySystemComponent)
	{
		return;
	}

	SetTestAbilities();
	FGameplayEffectContextHandle effectContext = abilitySystemComponent->MakeEffectContext();
	effectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle vigorHandle = abilitySystemComponent->MakeOutgoingSpec(vigorAttributeEffects, vigorLevel, effectContext);

	if (vigorHandle.IsValid())
	{
		FActiveGameplayEffectHandle activeHandle = abilitySystemComponent->ApplyGameplayEffectSpecToTarget(*vigorHandle.Data.Get(), abilitySystemComponent);
	}
	
	FGameplayEffectSpecHandle enduranceHandle = abilitySystemComponent->MakeOutgoingSpec(enduranceAttributeEffects, enduranceLevel, effectContext);

	if (enduranceHandle.IsValid())
	{
		FActiveGameplayEffectHandle activeHandle = abilitySystemComponent->ApplyGameplayEffectSpecToTarget(*enduranceHandle.Data.Get(), abilitySystemComponent);
	}
	
	FGameplayEffectSpecHandle strengthHandle = abilitySystemComponent->MakeOutgoingSpec(strengthAttributeEffects, strengthLevel, effectContext);

	if (strengthHandle.IsValid())
	{
		FActiveGameplayEffectHandle activeHandle = abilitySystemComponent->ApplyGameplayEffectSpecToTarget(*strengthHandle.Data.Get(), abilitySystemComponent);
	}

	FGameplayEffectSpecHandle dexterityHandle = abilitySystemComponent->MakeOutgoingSpec(dexterityAttributeEffects, dexterityLevel, effectContext);

	if (dexterityHandle.IsValid())
	{
		FActiveGameplayEffectHandle activeHandle = abilitySystemComponent->ApplyGameplayEffectSpecToTarget(*dexterityHandle.Data.Get(), abilitySystemComponent);
	}

	FGameplayEffectSpecHandle bloodLustHandle = abilitySystemComponent->MakeOutgoingSpec(bloodLustAttributeEffects, bloodLustLevel, effectContext);

	if (bloodLustHandle.IsValid())
	{
		FActiveGameplayEffectHandle activeHandle = abilitySystemComponent->ApplyGameplayEffectSpecToTarget(*bloodLustHandle.Data.Get(), abilitySystemComponent);
	}

	FGameplayEffectSpecHandle arcaneHandle = abilitySystemComponent->MakeOutgoingSpec(arcaneAttributeEffects, arcaneLevel, effectContext);

	if (arcaneHandle.IsValid())
	{
		FActiveGameplayEffectHandle activeHandle = abilitySystemComponent->ApplyGameplayEffectSpecToTarget(*arcaneHandle.Data.Get(), abilitySystemComponent);
	}
}

void ABaseCharacterController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (abilitySystemComponent)
	{
		abilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	InitializeAttributes();
}

void ABaseCharacterController::InitializeAttributes()
{
	if (abilitySystemComponent && defaultAttributeEffects)
	{
		FGameplayEffectContextHandle EffectContext = abilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		FGameplayEffectSpecHandle SpecHandle = abilitySystemComponent->MakeOutgoingSpec(defaultAttributeEffects, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = abilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ABaseCharacterController::GiveDefaultAbilities()
{
	if (HasAuthority() && abilitySystemComponent)
	{
		for (TSubclassOf<UGameplayAbility>& StartUpAbility : defaultAbilities)
		{
			abilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartUpAbility.GetDefaultObject(), 1, 0));
		}
	}
}

int32 ABaseCharacterController::GetCharacterLevel()
{
	characterLevel = vigorLevel + enduranceLevel + strengthLevel + dexterityLevel + bloodLustLevel + arcaneLevel;
	return characterLevel;
}

int32 ABaseCharacterController::GetVigor() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetVigor();
}

int32 ABaseCharacterController::GetMaxVigor() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetMaxVigor();
}

int32 ABaseCharacterController::GetEndurance() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetEndurance();
}

int32 ABaseCharacterController::GetMaxEndurance() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetMaxEndurance();
}

int32 ABaseCharacterController::GetStrength() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetStrength();
}

int32 ABaseCharacterController::GetMaxStrength() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetMaxStrength();
}

int32 ABaseCharacterController::GetDexterity() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetDexterity();
}

int32 ABaseCharacterController::GetMaxDexterity() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetMaxDexterity();
}

int32 ABaseCharacterController::GetBloodLust() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetBloodLust();
}

int32 ABaseCharacterController::GetMaxBloodLust() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetMaxBloodLust();
}

int32 ABaseCharacterController::GetArcane() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetArcane();
}

int32 ABaseCharacterController::GetMaxArcane() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetMaxArcane();
}

int32 ABaseCharacterController::GetBloodVials() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetBloodVials();
}

int32 ABaseCharacterController::GetMaxBloodVials() const
{
	if (!attributes)
	{
		return 0.0f;
	}

	return attributes->GetMaxBloodVials();
}

bool ABaseCharacterController::ActivateAbilitiesWithTag(FGameplayTagContainer AbilityTags, bool AllowRemoteActivation)
{
	if (!abilitySystemComponent)
	{
		return false;
	}
	
	return abilitySystemComponent->TryActivateAbilitiesByTag(AbilityTags, AllowRemoteActivation);
}

void ABaseCharacterController::SetTestAbilities()
{
	if (!abilitySystemComponent)
	{
		return;
	}

	if (GetLocalRole() == ROLE_Authority)
	{
		for (auto testAbility : defaultAbilities)
		{
			abilitySystemComponent->GiveAbility(FGameplayAbilitySpec(testAbility, GetCharacterLevel(), INDEX_NONE, this));
		}
	}
}

void ABaseCharacterController::HandleHealthChange(float DeltaValue, AActor* OtherActor)
{
	OnHealthChange(DeltaValue, OtherActor);

	if (GetVigor() <= 0)
	{
		OnDeath();
	}
}

void ABaseCharacterController::HandleStaminaChange(float DeltaValue, AActor* OtherActor)
{
	OnStaminaChange(DeltaValue, OtherActor);
}
