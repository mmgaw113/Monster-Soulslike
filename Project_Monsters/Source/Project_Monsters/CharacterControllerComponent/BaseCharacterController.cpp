// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterController.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffectTypes.h"
#include "Kismet/KismetMathLibrary.h"
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
	SetAttributeValues();
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

void ABaseCharacterController::SetAttributeValues()
{
	FGameplayEffectContextHandle effectContext = abilitySystemComponent->MakeEffectContext();
	effectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle vigorHandle = abilitySystemComponent->MakeOutgoingSpec(
		vigorAttributeEffects, vigorLevel, effectContext);

	if (vigorHandle.IsValid())
	{
		FActiveGameplayEffectHandle activeHandle = abilitySystemComponent->ApplyGameplayEffectSpecToTarget(
			*vigorHandle.Data.Get(), abilitySystemComponent);
	}

	FGameplayEffectSpecHandle enduranceHandle = abilitySystemComponent->MakeOutgoingSpec(
		enduranceAttributeEffects, enduranceLevel, effectContext);

	if (enduranceHandle.IsValid())
	{
		FActiveGameplayEffectHandle activeHandle = abilitySystemComponent->ApplyGameplayEffectSpecToTarget(
			*enduranceHandle.Data.Get(), abilitySystemComponent);
	}

	FGameplayEffectSpecHandle strengthHandle = abilitySystemComponent->MakeOutgoingSpec(
		strengthAttributeEffects, strengthLevel, effectContext);

	if (strengthHandle.IsValid())
	{
		FActiveGameplayEffectHandle activeHandle = abilitySystemComponent->ApplyGameplayEffectSpecToTarget(
			*strengthHandle.Data.Get(), abilitySystemComponent);
	}

	FGameplayEffectSpecHandle dexterityHandle = abilitySystemComponent->MakeOutgoingSpec(
		dexterityAttributeEffects, dexterityLevel, effectContext);

	if (dexterityHandle.IsValid())
	{
		FActiveGameplayEffectHandle activeHandle = abilitySystemComponent->ApplyGameplayEffectSpecToTarget(
			*dexterityHandle.Data.Get(), abilitySystemComponent);
	}

	FGameplayEffectSpecHandle bloodLustHandle = abilitySystemComponent->MakeOutgoingSpec(
		bloodLustAttributeEffects, bloodLustLevel, effectContext);

	if (bloodLustHandle.IsValid())
	{
		FActiveGameplayEffectHandle activeHandle = abilitySystemComponent->ApplyGameplayEffectSpecToTarget(
			*bloodLustHandle.Data.Get(), abilitySystemComponent);
	}

	FGameplayEffectSpecHandle arcaneHandle = abilitySystemComponent->MakeOutgoingSpec(
		arcaneAttributeEffects, arcaneLevel, effectContext);

	if (bloodLustHandle.IsValid())
	{
		FActiveGameplayEffectHandle activeHandle = abilitySystemComponent->ApplyGameplayEffectSpecToTarget(
			*arcaneHandle.Data.Get(), abilitySystemComponent);
	}
}

void ABaseCharacterController::InitializeAttributes()
{
	if (abilitySystemComponent && defaultAttributeEffects)
	{
		FGameplayEffectContextHandle EffectContext = abilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		FGameplayEffectSpecHandle SpecHandle = abilitySystemComponent->MakeOutgoingSpec(
			defaultAttributeEffects, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = abilitySystemComponent->ApplyGameplayEffectSpecToSelf(
				*SpecHandle.Data.Get());
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

int32 ABaseCharacterController::CalculateMaxHealth(int Vigor) const
{
	if (UKismetMathLibrary::InRange_IntInt(Vigor, 1, 25))
	{
		float charLevel = Vigor - 1;
		float resultHealth = FMath::Pow(charLevel / 24, 1.5);
		return 300 + 500 * resultHealth;
	}
	else if (UKismetMathLibrary::InRange_IntInt(Vigor, 25, 40))
	{
		float charLevel = Vigor - 25;
		float resultHealth = FMath::Pow(charLevel / 15, 1.1);
		return 800 + 650 * resultHealth;
	}
	else if (UKismetMathLibrary::InRange_IntInt(Vigor, 40, 60))
	{
		float charLevel = Vigor - 40;
		float resultHealth = 1 - (1 - FMath::Pow(charLevel / 20, 1.2));
		return 1450 + 450 * resultHealth;
	}
	else if ((UKismetMathLibrary::InRange_IntInt(Vigor, 60, 99)))
	{
		float charLevel = Vigor - 60;
		float resultHealth = 1 - (1 - FMath::Pow(charLevel / 39, 1.2));
		return 1900 + 200 * resultHealth;
	}

	float charLevel = 99 - 60;
	float resultHealth = 1 - (1 - FMath::Pow(charLevel / 39, 1.2));
	return 1900 + 200 * resultHealth;
}

int32 ABaseCharacterController::CalculateMaxStamina(int Endurance) const
{
	if (UKismetMathLibrary::InRange_IntInt(Endurance, 1, 15))
	{
		float charLevel = Endurance - 1;
		float resultStamina = charLevel / 14;
		return 80 + 25 * resultStamina;
	}
	else if (UKismetMathLibrary::InRange_IntInt(Endurance, 16, 35))
	{
		float charLevel = Endurance - 15;
		float resultStamina = charLevel / 15;
		return 105 + 25 * resultStamina;
	}
	else if (UKismetMathLibrary::InRange_IntInt(Endurance, 36, 60))
	{
		float charLevel = Endurance - 30;
		float resultStamina = charLevel / 20;
		return 120 + 25 * resultStamina;
	}
	else if (UKismetMathLibrary::InRange_IntInt(Endurance, 61, 99))
	{
		float charLevel = Endurance - 50;
		float resultStamina = charLevel / 49;
		return 155 + 15 * resultStamina;
	}

	float charLevel = 99 - 50;
	float resultStamina = charLevel / 49;
	return 155 + 15 * resultStamina;
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
			abilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(testAbility, GetCharacterLevel(), INDEX_NONE, this));
		}
	}
}

void ABaseCharacterController::HandleHealthChange(int32 DeltaValue, AActor* OtherActor)
{
	OnHealthChange(DeltaValue, OtherActor);

	if (health <= 0)
	{
		OnDeath();
	}
}

void ABaseCharacterController::HandleStaminaChange(float DeltaValue, AActor* OtherActor)
{
	OnStaminaChange(DeltaValue, OtherActor);
}
