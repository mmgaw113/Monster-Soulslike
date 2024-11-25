// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetingComponent.generated.h"


class UCameraComponent;
class APlayerCharacterController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_MONSTERS_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void LockOnToTarget();
	void LockOnToTargetLeft();
	void LockOnToTargetRight();

	bool lockedOn;
	APlayerCharacterController* playerController;
	UCameraComponent* playerCamera;

private:
	float radius = 1000.0f;
	AActor* lockedOnActor;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<AActor*> FindActorsToLockOnTo();
	AActor* FindClosestTarget(TArray<AActor*> Actors);
	AActor* FindClosestTargetLeft(TArray<AActor*> Actors);
	AActor* FindClosestTargetRight(TArray<AActor*> Actors);
	float TargetDistanceCheck(AActor* Target);
	void OrientCamera();
	void LookAtTarget();
};
