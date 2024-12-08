// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpScreen.h"

#include "PlayerHud.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Monsters/Attributes/TheHuntAttributeSet.h"
#include "Project_Monsters/CharacterControllerComponent/PlayerCharacterController.h"

void ULevelUpScreen::NativeConstruct()
{
	Super::NativeConstruct();

	SetVigor();
	SetEndurance();
	SetStrength();
	SetDexterity();
	SetBloodLust();
	SetArcane();
	SetHealth();
	SetStamina();
	SetCharacterLevel();

	if (IncreaseVigor)
	{
		IncreaseVigor->OnClicked.AddDynamic(this, &ULevelUpScreen::AdjustVigorUp);
	}

	if (Submit)
	{
		Submit->OnClicked.AddDynamic(this, &ULevelUpScreen::OnSubmit);
	}
}

void ULevelUpScreen::SetVigor()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		Vigor->SetText(FText::FromString("Vigor: " + FString::FromInt(character->vigorLevel)));
	}
}

void ULevelUpScreen::SetEndurance()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		Endurance->SetText(FText::FromString("Endurance: " + FString::FromInt(character->attributes->Endurance.GetCurrentValue())));
	}
}

void ULevelUpScreen::SetStrength()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		Strength->SetText(FText::FromString("Strength: " + FString::FromInt(character->attributes->Strength.GetCurrentValue())));
	}
}

void ULevelUpScreen::SetDexterity()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		Dexterity->SetText(FText::FromString("Dexterity: " + FString::FromInt(character->attributes->Dexterity.GetCurrentValue())));
	}
}

void ULevelUpScreen::SetBloodLust()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		BloodLust->SetText(FText::FromString("Blood Lust: " + FString::FromInt(character->attributes->BloodLust.GetCurrentValue())));
	}
}

void ULevelUpScreen::SetArcane()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		Arcane->SetText(FText::FromString("Arcane: " + FString::FromInt(character->attributes->Arcane.GetCurrentValue())));
	}
}

void ULevelUpScreen::SetHealth()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		Health->SetText(FText::FromString("Health: " + FString::FromInt(character->CalculateMaxHealth(character->vigorLevel))));
	}
}

void ULevelUpScreen::SetStamina()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		Stamina->SetText(FText::FromString("Stamina: " + FString::FromInt(character->CalculateMaxStamina(character->attributes->Endurance.GetCurrentValue()))));
	}
}

void ULevelUpScreen::SetCharacterLevel()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		CharacterLevel->SetText(FText::FromString("Character Level: " + FString::FromInt(character->GetCharacterLevel())));
	}
}

void ULevelUpScreen::AdjustVigorUp()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		Vigor->SetText(FText::FromString("Vigor: " + FString::FromInt(character->vigorLevel += 1)));
		SetHealth();
		character->playerHud->SetHealthBarSize();
	}
}

void ULevelUpScreen::AdjustEnduranceUp()
{
	
}

void ULevelUpScreen::AdjustStrengthUp()
{
	
}

void ULevelUpScreen::AdjustDexterityUp()
{
	
}

void ULevelUpScreen::AdjustBloodLustUp()
{
	
}

void ULevelUpScreen::AdjustArcaneUp()
{
	
}

void ULevelUpScreen::AdjustVigorDown()
{
	
}

void ULevelUpScreen::AdjustEnduranceDown()
{
	
}

void ULevelUpScreen::AdjustStrengthDown()
{
	
}

void ULevelUpScreen::AdjustDexterityDown()
{

}

void ULevelUpScreen::AdjustBloodLustDown()
{
	
}

void ULevelUpScreen::AdjustArcaneDown()
{
	
}

void ULevelUpScreen::OnSubmit()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		character->SetAttributeValues();
		character->maxHealth = character->CalculateMaxHealth(character->vigorLevel);
		character->health =	character->maxHealth;
	}
}
