// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"

#include "Components/ProgressBar.h"

void UPlayerHud::NativeConstruct()
{
	gameInstance = Cast<UTheHuntGameInstance>(GetGameInstance());
}

void UPlayerHud::SetHealth(int32 CurrentHealth, int32 MaxHealth)
{
	if (healthBar)
	{
		healthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}

void UPlayerHud::SetHealthBuffer(int32 CurrentHealth, int32 MaxHealth)
{
	if (healthBarBuffer)
	{
		healthBarBuffer->SetPercent(CurrentHealth / MaxHealth);			
	}
}

void UPlayerHud::SetStamina(int32 CurrentStamina, int32 MaxStamina)
{
	if (staminaBar)
	{
		staminaBar->SetPercent(CurrentStamina / MaxStamina);
	}
}
