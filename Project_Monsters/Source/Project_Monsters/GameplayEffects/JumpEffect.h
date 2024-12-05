// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "JumpEffect.generated.h"

UCLASS()
class PROJECT_MONSTERS_API UJumpEffect : public UGameplayEffect
{
	GENERATED_BODY()
	
	UJumpEffect();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess))
	FGameplayModifierInfo EffectInfo;
};
