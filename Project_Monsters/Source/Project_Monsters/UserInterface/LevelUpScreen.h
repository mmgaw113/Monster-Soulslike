// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpScreen.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_MONSTERS_API ULevelUpScreen : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* Vigor;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* Health;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* Endurance;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* Stamina;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* Strength;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* Dexterity;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* BloodLust;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* Arcane;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* CharacterLevel;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* BloodVialsHeld;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* BloodVialsNeeded;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* IncreaseVigor;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* DecreaseVigor;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* IncreaseEndurance;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* DecreaseEndurance;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* IncreaseStrength;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* DecreaseStrength;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* IncreaseDexterity;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* DecreaseDexterity;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* IncreaseBloodLust;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* DecreaseBloodLust;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* IncreaseArcane;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* DecreaseArcane;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Submit;

	// Set Functions
	void SetVigor();
	void SetEndurance();
	void SetStrength();
	void SetDexterity();
	void SetBloodLust();
	void SetArcane();
	void SetHealth();
	void SetStamina();

	UFUNCTION()
	void SetCharacterLevel();
	UFUNCTION()
	void AdjustVigorUp();
	UFUNCTION()
	void AdjustEnduranceUp();
	UFUNCTION()
	void AdjustStrengthUp();
	UFUNCTION()
	void AdjustDexterityUp();
	UFUNCTION()
	void AdjustBloodLustUp();
	UFUNCTION()
	void AdjustArcaneUp();
	
	void AdjustVigorDown();
	void AdjustEnduranceDown();
	void AdjustStrengthDown();
	void AdjustDexterityDown();
	void AdjustBloodLustDown();
	void AdjustArcaneDown();

	UFUNCTION()
	void OnSubmit();
};
