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

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, Health);
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, Vigor);
	UFUNCTION()
	virtual void OnRep_Vigor(const FGameplayAttributeData& OldVigor);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Endurance;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, Endurance);
	UFUNCTION()
	virtual void OnRep_Endurance(const FGameplayAttributeData& OldEndurance);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, Stamina);
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, Strength);
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, Dexterity);
	virtual void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData BloodLust;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, BloodLust);
	virtual void OnRep_BloodLust(const FGameplayAttributeData& OldBloodLust);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Arcane;
	ATTRIBUTE_ACCESSORS(UTheHuntAttributeSet, Arcane);
	virtual void OnRep_Arcane(const FGameplayAttributeData& OldArcane);
};
