// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TheHuntAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROJECT_MONSTERS_API UTheHuntAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UTheHuntAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_Vigor)
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, Vigor);
	UFUNCTION()
	virtual void OnRep_Vigor(const FGameplayAttributeData& OldVigor);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_MaxVigor)
	FGameplayAttributeData MaxVigor;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, MaxVigor);
	UFUNCTION()
	virtual void OnRep_MaxVigor(const FGameplayAttributeData& OldMaxVigor);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_Endurance)
	FGameplayAttributeData Endurance;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, Endurance);
	UFUNCTION()
	virtual void OnRep_Endurance(const FGameplayAttributeData& OldEndurance);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_MaxEndurance)
	FGameplayAttributeData MaxEndurance;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, MaxEndurance);
	UFUNCTION()
	virtual void OnRep_MaxEndurance(const FGameplayAttributeData& OldMaxEndurance);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, Strength);
	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_MaxStrength)
	FGameplayAttributeData MaxStrength;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, MaxStrength);
	UFUNCTION()
	virtual void OnRep_MaxStrength(const FGameplayAttributeData& OldMaxStrength);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_Dexterity)
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, Dexterity);
	UFUNCTION()
	virtual void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_MaxDexterity)
	FGameplayAttributeData MaxDexterity;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, MaxDexterity);
	UFUNCTION()
	virtual void OnRep_MaxDexterity(const FGameplayAttributeData& OldMaxDexterity);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_BloodLust)
	FGameplayAttributeData BloodLust;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, BloodLust);
	UFUNCTION()
	virtual void OnRep_BloodLust(const FGameplayAttributeData& OldBloodLust);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_MaxBloodLust)
	FGameplayAttributeData MaxBloodLust;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, MaxBloodLust);
	UFUNCTION()
	virtual void OnRep_MaxBloodLust(const FGameplayAttributeData& OldMaxBloodLust);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_Arcane)
	FGameplayAttributeData Arcane;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, Arcane);
	UFUNCTION()
	virtual void OnRep_Arcane(const FGameplayAttributeData& OldArcane);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_MaxArcane)
	FGameplayAttributeData MaxArcane;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, MaxArcane);
	UFUNCTION()
	virtual void OnRep_MaxArcane(const FGameplayAttributeData& OldMaxArcane);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_BloodVials)
	FGameplayAttributeData BloodVials;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, BloodVials);
	UFUNCTION()
	virtual void OnRep_BloodVials(const FGameplayAttributeData& OldBloodVials);

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing = OnRep_MaxBloodVials)
	FGameplayAttributeData MaxBloodVials;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, MaxBloodVials);
	UFUNCTION()
	virtual void OnRep_MaxBloodVials(const FGameplayAttributeData& OldMaxBloodVials);

protected:
	void AdjustAttrbuteForMaxChange(FGameplayAttributeData& AffectedAttribute,
		const FGameplayAttributeData MaxAttribute,
		float NewMaxValue,
		const FGameplayAttribute AffectedAttributeProperty);
};
