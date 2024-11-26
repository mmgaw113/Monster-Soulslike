// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"

#include "Components/ProgressBar.h"

void UPlayerHud::NativeConstruct()
{
	gameInstance = Cast<UTheHuntGameInstance>(GetGameInstance());
}

void UPlayerHud::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (healthBar)
	{
		healthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}

void UPlayerHud::SetStamina(float CurrentStamina, float MaxStamina)
{
	if (staminaBar)
	{
		staminaBar->SetPercent(CurrentStamina / MaxStamina);
	}
}
