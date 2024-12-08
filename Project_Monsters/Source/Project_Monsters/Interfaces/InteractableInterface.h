// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_MONSTERS_API IInteractableInterface
{
	GENERATED_BODY()


public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Interact();
};
