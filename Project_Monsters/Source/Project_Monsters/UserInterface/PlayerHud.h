// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Project_Monsters/GameInstance/TheHuntGameInstance.h"
#include "PlayerHud.generated.h"

UCLASS()
class PROJECT_MONSTERS_API UPlayerHud : public UUserWidget
{
	GENERATED_BODY()
	
	UTheHuntGameInstance* gameInstance;

	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UProgressBar* healthBar;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* healthBarBuffer;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* staminaBar;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UCanvasPanel* healthBarCanvas;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UCanvasPanel* staminaBarCanvas;
	
	void SetHealth(float CurrentHealth, float MaxHealth);
	void SetHealthBuffer(float CurrentHealth, float MaxHealth);
	void SetStamina(float CurrentStamina, float MaxStamina);
};