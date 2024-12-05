// Fill out your copyright notice in the Description page of Project Settings.


#include "RechargeStaminaEffect.h"
#include "Project_Monsters/Attributes/TheHuntAttributeSet.h"

URechargeStaminaEffect::URechargeStaminaEffect()
{
	EffectInfo.Attribute = UTheHuntAttributeSet::GetEnduranceAttribute();
	EffectInfo.ModifierOp = EGameplayModOp::Additive;
	EffectInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude( 0.35f);	
	Modifiers.Add(EffectInfo); 
}
