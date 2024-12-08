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

	void SetHealth(int32 CurrentHealth, int32 MaxHealth);
	void SetHealthBuffer(int32 CurrentHealth, int32 MaxHealth);
	void SetStamina(float CurrentStamina, float MaxStamina);
};
