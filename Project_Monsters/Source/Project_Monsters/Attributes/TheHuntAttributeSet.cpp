// Fill out your copyright notice in the Description page of Project Settings.


#include "TheHuntAttributeSet.h"
#include "Net/UnrealNetwork.h"

UTheHuntAttributeSet::UTheHuntAttributeSet()
{
	
}

void UTheHuntAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(UTheHuntAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTheHuntAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTheHuntAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTheHuntAttributeSet, Endurance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTheHuntAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTheHuntAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTheHuntAttributeSet, BloodLust, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTheHuntAttributeSet, Arcane, COND_None, REPNOTIFY_Always);
}

void UTheHuntAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, Health, OldHealth);
}

void UTheHuntAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, Vigor, OldVigor);
}

void UTheHuntAttributeSet::OnRep_Endurance(const FGameplayAttributeData& OldEndurance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, Endurance, OldEndurance);
}

void UTheHuntAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, Stamina, OldStamina);
}

void UTheHuntAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, Strength, OldStrength);
}

void UTheHuntAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, Dexterity, OldDexterity);
}

void UTheHuntAttributeSet::OnRep_BloodLust(const FGameplayAttributeData& OldBloodLust)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, BloodLust, OldBloodLust);
}

void UTheHuntAttributeSet::OnRep_Arcane(const FGameplayAttributeData& OldArcane)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTheHuntAttributeSet, Arcane, OldArcane);
}