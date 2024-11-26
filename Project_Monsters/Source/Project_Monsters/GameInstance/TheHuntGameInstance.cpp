// Fill out your copyright notice in the Description page of Project Settings.


#include "TheHuntGameInstance.h"

void UTheHuntGameInstance::Init()
{
	PlayerAttributes.CurrentHealth = PlayerAttributes.MaxHealth;
	PlayerAttributes.CurrentStamina = PlayerAttributes.MaxStamina;
}
