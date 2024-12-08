// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project_Monsters/Interfaces/InteractableInterface.h"
#include "Bonfire.generated.h"

UCLASS()
class PROJECT_MONSTERS_API ABonfire : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	ABonfire();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation() override;

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(allowPrivateAccess=true))
	TSubclassOf<UUserWidget> levelUpClass;
	UPROPERTY()
	UUserWidget* levelUpScreen;
};
