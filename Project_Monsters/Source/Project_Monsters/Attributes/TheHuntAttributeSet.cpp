// Fill out your copyright notice in the Description page of Project Settings.


#include "TheHuntAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Project_Monsters/CharacterControllerComponent/BaseCharacterController.h"

UTheHuntAttributeSet::UTheHuntAttributeSet()
{
}

void UTheHuntAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(UTheHuntAttributeSet, Vigor);
	DOREPLIFETIME(UTheHuntAttributeSet, MaxVigor);
	DOREPLIFETIME(UTheHuntAttributeSet, Endurance);
	DOREPLIFETIME(UTheHuntAttributeSet, MaxEndurance);
	DOREPLIFETIME(UTheHuntAttributeSet, Strength);
	DOREPLIFETIME(UTheHuntAttributeSet, MaxStrength);
	DOREPLIFETIME(UTheHuntAttributeSet, Dexterity);
	DOREPLIFETIME(UTheHuntAttributeSet, MaxDexterity);
	DOREPLIFETIME(UTheHuntAttributeSet, BloodLust);
	DOREPLIFETIME(UTheHuntAttributeSet, MaxBloodLust);
	DOREPLIFETIME(UTheHuntAttributeSet, Arcane);
	DOREPLIFETIME(UTheHuntAttributeSet, MaxArcane);
	DOREPLIFETIME(UTheHuntAttributeSet, BloodVials);
	DOREPLIFETIME(UTheHuntAttributeSet, MaxBloodVials);
}

void UTheHuntAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);


	if (Data.EvaluatedData.Attribute == GetVigorAttribute())
	{
		SetVigor(FMath::Clamp(GetVigor(), 0.0f, 99.0f));
	}

	if (Data.EvaluatedData.Attribute == GetEnduranceAttribute())
	{
		SetEndurance(FMath::Clamp(GetEndurance(), 0.0f, 99.0f));
	}

	if (Data.EvaluatedData.Attribute == GetStrengthAttribute())
	{
		SetStrength(FMath::Clamp(GetStrength(), 0.0f, 99.0f));
	}

	if (Data.EvaluatedData.Attribute == GetDexterityAttribute())
	{
		SetDexterity(FMath::Clamp(GetDexterity(), 0.0f, 99.0f));
	}

	if (Data.EvaluatedData.Attribute == GetBloodLustAttribute())
	{
		SetBloodLust(FMath::Clamp(GetBloodLust(), 0.0f, 99.0f));
	}

	if (Data.EvaluatedData.Attribute == GetArcaneAttribute())
	{
		SetArcane(FMath::Clamp(GetArcane(), 0.0f, 99.0f));
	}

	if (Data.EvaluatedData.Attribute == GetBloodVialsAttribute())
	{
		SetBloodVials(FMath::Clamp(GetBloodVials(), 0.0f, 99.0f));
	}
}

void UTheHuntAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxVigorAttribute())
	{
		AdjustAttrbuteForMaxChange(Vigor, MaxVigor, NewValue, GetVigorAttribute());
	}

	if (Attribute == GetMaxEnduranceAttribute())
	{
		AdjustAttrbuteForMaxChange(Endurance, MaxEndurance, NewValue, GetEnduranceAttribute());
	}

	if (Attribute == GetMaxStrengthAttribute())
	{
		AdjustAttrbuteForMaxChange(Strength, MaxStrength, NewValue, GetStrengthAttribute());
	}

	if (Attribute == GetMaxDexterityAttribute())
	{
		AdjustAttrbuteForMaxChange(Dexterity, MaxDexterity, NewValue, GetDexterityAttribute());
	}

	if (Attribute == GetMaxBloodLustAttribute())
	{
		AdjustAttrbuteForMaxChange(BloodLust, MaxBloodLust, NewValue, GetBloodLustAttribute());
	}

	if (Attribute == GetMaxArcaneAttribute())
	{
		AdjustAttrbuteForMaxChange(Arcane, MaxArcane, NewValue, GetArcaneAttribute());
	}
}

void UTheHuntAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, Vigor, OldVigor);
}

void UTheHuntAttributeSet::OnRep_MaxVigor(const FGameplayAttributeData& OldMaxVigor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, MaxVigor, OldMaxVigor);
}

void UTheHuntAttributeSet::OnRep_Endurance(const FGameplayAttributeData& OldEndurance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, Endurance, OldEndurance);
}

void UTheHuntAttributeSet::OnRep_MaxEndurance(const FGameplayAttributeData& OldMaxEndurance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, MaxEndurance, OldMaxEndurance);
}

void UTheHuntAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, Strength, OldStrength);
}

void UTheHuntAttributeSet::OnRep_MaxStrength(const FGameplayAttributeData& OldMaxStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, MaxStrength, OldMaxStrength);
}

void UTheHuntAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, Dexterity, OldDexterity);
}

void UTheHuntAttributeSet::OnRep_MaxDexterity(const FGameplayAttributeData& OldMaxDexterity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, MaxDexterity, OldMaxDexterity);
}

void UTheHuntAttributeSet::OnRep_BloodLust(const FGameplayAttributeData& OldBloodLust)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, BloodLust, OldBloodLust);
}

void UTheHuntAttributeSet::OnRep_MaxBloodLust(const FGameplayAttributeData& OldMaxBloodLust)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, MaxBloodLust, OldMaxBloodLust);
}

void UTheHuntAttributeSet::OnRep_Arcane(const FGameplayAttributeData& OldArcane)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, Arcane, OldArcane);
}

void UTheHuntAttributeSet::OnRep_MaxArcane(const FGameplayAttributeData& OldMaxArcane)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, MaxArcane, OldMaxArcane);
}

void UTheHuntAttributeSet::OnRep_BloodVials(const FGameplayAttributeData& OldBloodVials)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, BloodVials, OldBloodVials);
}

void UTheHuntAttributeSet::OnRep_MaxBloodVials(const FGameplayAttributeData& OldMaxBloodVials)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, MaxBloodVials, OldMaxBloodVials);
}

void UTheHuntAttributeSet::AdjustAttrbuteForMaxChange(FGameplayAttributeData& AffectedAttribute,
                                                      const FGameplayAttributeData MaxAttribute, float NewMaxValue,
                                                      const FGameplayAttribute AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilitySystemComponent = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();

	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilitySystemComponent)
	{
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = CurrentMaxValue > 0.f
			                 ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue
			                 : NewMaxValue;
		AbilitySystemComponent->ApplyModToAttribute(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}
