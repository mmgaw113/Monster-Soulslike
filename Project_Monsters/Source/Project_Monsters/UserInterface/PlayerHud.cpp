// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"

#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Monsters/CharacterControllerComponent/PlayerCharacterController.h"

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

void UPlayerHud::SetStamina(float CurrentStamina, float MaxStamina)
{
	if (staminaBar)
	{
		staminaBar->SetPercent(CurrentStamina / MaxStamina);
	}
}

void UPlayerHud::SetHealthBarSize()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (healthBarCanvas)
		{
			healthBarCanvas->GetDesiredSize().Set(healthBarCanvas->GetDesiredSize().X, character->CalculateMaxHealth(character->vigorLevel));
		}
	}
}

void UPlayerHud::SetStaminaBarSize(float NewValue)
{
}
