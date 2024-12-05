// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintEffect.h"
#include "Project_Monsters/Attributes/TheHuntAttributeSet.h"

USprintEffect::USprintEffect()
{
	EffectInfo.Attribute = UTheHuntAttributeSet::GetEnduranceAttribute();
	EffectInfo.ModifierOp = EGameplayModOp::Additive;
	EffectInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude( -1.0f);	
	Modifiers.Add(EffectInfo); 
}
