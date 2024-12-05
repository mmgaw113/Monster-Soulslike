// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpEffect.h"
#include "Project_Monsters/Attributes/TheHuntAttributeSet.h"

UJumpEffect::UJumpEffect()
{
	EffectInfo.Attribute = UTheHuntAttributeSet::GetEnduranceAttribute();
	EffectInfo.ModifierOp = EGameplayModOp::Additive;
	EffectInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude( -15.0f);
	Modifiers.Add(EffectInfo); 
}
