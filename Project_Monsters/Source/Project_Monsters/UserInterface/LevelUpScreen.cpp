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
		IncreaseVigor->OnClicked.AddDynamic(this, &ULevelUpScreen::SetCharacterLevel);
	}

	if (IncreaseEndurance)
	{
		IncreaseEndurance->OnClicked.AddDynamic(this, &ULevelUpScreen::AdjustEnduranceUp);
		IncreaseEndurance->OnClicked.AddDynamic(this, &ULevelUpScreen::SetCharacterLevel);
	}

	if (IncreaseStrength)
	{
		IncreaseStrength->OnClicked.AddDynamic(this, &ULevelUpScreen::AdjustStrengthUp);
		IncreaseStrength->OnClicked.AddDynamic(this, &ULevelUpScreen::SetCharacterLevel);
	}

	if (IncreaseDexterity)
	{
		IncreaseDexterity->OnClicked.AddDynamic(this, &ULevelUpScreen::AdjustDexterityUp);
		IncreaseDexterity->OnClicked.AddDynamic(this, &ULevelUpScreen::SetCharacterLevel);
	}

	if (IncreaseBloodLust)
	{
		IncreaseBloodLust->OnClicked.AddDynamic(this, &ULevelUpScreen::AdjustBloodLustUp);
		IncreaseBloodLust->OnClicked.AddDynamic(this, &ULevelUpScreen::SetCharacterLevel);
	}

	if (IncreaseArcane)
	{
		IncreaseArcane->OnClicked.AddDynamic(this, &ULevelUpScreen::AdjustArcaneUp);
		IncreaseArcane->OnClicked.AddDynamic(this, &ULevelUpScreen::SetCharacterLevel);
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
		Stamina->SetText(FText::FromString("Stamina: " + FString::FromInt(character->CalculateMaxStamina(character->enduranceLevel))));
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
		if (character->vigorLevel < 99)
		{
			Vigor->SetText(FText::FromString("Vigor: " + FString::FromInt(character->vigorLevel += 1)));
			SetHealth();	
		}
	}
}

void ULevelUpScreen::AdjustEnduranceUp()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (character->enduranceLevel < 99)
		{
			Endurance->SetText(FText::FromString("Endurance: " + FString::FromInt(character->enduranceLevel += 1)));
			SetStamina();	
		}
	}
}

void ULevelUpScreen::AdjustStrengthUp()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (character->strengthLevel < 99)
		{
			Strength->SetText(FText::FromString("Strength: " + FString::FromInt(character->strengthLevel += 1)));
		}
	}
}

void ULevelUpScreen::AdjustDexterityUp()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (character->dexterityLevel < 99)
		{
			Dexterity->SetText(FText::FromString("Dexterity: " + FString::FromInt(character->dexterityLevel += 1)));
		}
	}
}

void ULevelUpScreen::AdjustBloodLustUp()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (character->bloodLustLevel < 99)
		{
			BloodLust->SetText(FText::FromString("Blood Lust: " + FString::FromInt(character->bloodLustLevel += 1)));
		}
	}
}

void ULevelUpScreen::AdjustArcaneUp()
{
	if (auto character = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (character->arcaneLevel < 99)
		{
			Arcane->SetText(FText::FromString("Arcane: " + FString::FromInt(character->arcaneLevel += 1)));
		}
	}
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
		character->maxStamina = character->CalculateMaxStamina(character->enduranceLevel);
		character->stamina = character->maxStamina;
		character->GetCharacterLevel();
		this->RemoveFromParent();
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	}
}
