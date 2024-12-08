// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_Monsters/CharacterControllerComponent/PlayerCharacterController.h"
#include "Project_Monsters/Interfaces/TargetingInterface.h"

// Sets default values for this component's properties
UTargetingComponent::UTargetingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();

	playerController = Cast<APlayerCharacterController>(GetOwner());
	playerCamera = Cast<UCameraComponent>(playerController->GetComponentByClass(UCameraComponent::StaticClass()));
}


// Called every frame
void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (lockedOn)
	{
		LookAtTarget();
	}
}

float UTargetingComponent::TargetDistanceCheck(AActor* Target)
{
	return FVector::DotProduct(playerCamera->GetForwardVector(),
	                           UKismetMathLibrary::MakeRotFromX(
		                           UKismetMathLibrary::FindLookAtRotation(
			                           playerController->GetActorLocation(),
			                           Target->GetActorLocation()).Vector()).Vector());
}


AActor* UTargetingComponent::FindClosestTarget(TArray<AActor*> Actors)
{
	FHitResult outHit;
	TArray<AActor*> actorsToIgnore;
	float distanceToTarget = 0.0f;
	AActor* closestTarget = nullptr;

	for (auto Actor : Actors)
	{
		if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), playerCamera->GetComponentLocation(),
		                                          Actor->GetActorLocation(), TraceTypeQuery1, false, actorsToIgnore,
		                                          EDrawDebugTrace::None, outHit, true))
		{
			if (TargetDistanceCheck(Actor) > distanceToTarget)
			{
				distanceToTarget = TargetDistanceCheck(Actor);
				closestTarget = Actor;
			}
		}
	}
	return closestTarget;
}

AActor* UTargetingComponent::FindClosestTargetLeft(TArray<AActor*> Actors)
{
	FHitResult outHit;
	TArray<AActor*> actorsToIgnore;
	float distanceToTarget = 0.0f;
	AActor* closestTarget = nullptr;

	for (auto Actor : Actors)
	{
		if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), playerCamera->GetComponentLocation(),
		                                          Actor->GetActorLocation(), TraceTypeQuery1, false, actorsToIgnore,
		                                          EDrawDebugTrace::None, outHit, true) &&
			FVector::DotProduct(playerCamera->GetRightVector(), outHit.Normal) > 0 && lockedOnActor != Actor)
		{
			if (TargetDistanceCheck(Actor) > distanceToTarget)
			{
				auto distance = FString::SanitizeFloat(distanceToTarget);
				distanceToTarget = TargetDistanceCheck(Actor);
				closestTarget = Actor;
			}
		}
	}
	return closestTarget;
}

AActor* UTargetingComponent::FindClosestTargetRight(TArray<AActor*> Actors)
{
	FHitResult outHit;
	TArray<AActor*> actorsToIgnore;
	float distanceToTarget = 0.0f;
	AActor* closestTarget = nullptr;

	for (auto Actor : Actors)
	{
		if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), playerCamera->GetComponentLocation(),
		                                          Actor->GetActorLocation(), TraceTypeQuery1, false, actorsToIgnore,
		                                          EDrawDebugTrace::None, outHit, true) &&
			FVector::DotProduct(playerCamera->GetRightVector(), outHit.Normal) < 0 && lockedOnActor != Actor)
		{
			if (TargetDistanceCheck(Actor) > distanceToTarget)
			{
				distanceToTarget = TargetDistanceCheck(Actor);
				closestTarget = Actor;
			}
		}
	}
	return closestTarget;
}

TArray<AActor*> UTargetingComponent::FindActorsToLockOnTo()
{
	auto traceStart = playerController->GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));
	TArray<FHitResult> hitResults;
	TArray<AActor*> actorsToIgnore = {GetOwner()};
	TArray<AActor*> potentialTargetedActors;

	if (UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), traceStart, traceStart, radius, ObjectTypesArray,
	                                                     false, actorsToIgnore, EDrawDebugTrace::None, hitResults,
	                                                     true))
	{
		for (auto outHit : hitResults)
		{
			if (outHit.GetActor()->GetClass()->ImplementsInterface(UTargetingInterface::StaticClass()))
			{
				potentialTargetedActors.Add(outHit.GetActor());
			}
		}
	}
	return potentialTargetedActors;
}

void UTargetingComponent::LockOnToTarget()
{
	if (!lockedOn)
	{
		if (FindClosestTarget(FindActorsToLockOnTo()))
		{
			lockedOnActor = FindClosestTarget(FindActorsToLockOnTo());
			OrientCamera();
			lockedOn = true;
			ITargetingInterface::Execute_DisplayLockedOnWidget(lockedOnActor, true);
		}
	}
	else
	{
		ITargetingInterface::Execute_DisplayLockedOnWidget(lockedOnActor, false);
		lockedOnActor = nullptr;
		playerController->GetCharacterMovement()->bOrientRotationToMovement = true;
		playerController->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		lockedOn = false;
	}
}

void UTargetingComponent::LockOnToTargetLeft()
{
	if (lockedOnActor)
	{
		if (FindClosestTargetLeft(FindActorsToLockOnTo()))
		{
			ITargetingInterface::Execute_DisplayLockedOnWidget(lockedOnActor, false);
			lockedOnActor = FindClosestTargetLeft(FindActorsToLockOnTo());
			ITargetingInterface::Execute_DisplayLockedOnWidget(lockedOnActor, true);
		}
	}
}

void UTargetingComponent::LockOnToTargetRight()
{
	if (lockedOnActor)
	{
		if (FindClosestTargetRight(FindActorsToLockOnTo()))
		{
			ITargetingInterface::Execute_DisplayLockedOnWidget(lockedOnActor, false);
			lockedOnActor = FindClosestTargetRight(FindActorsToLockOnTo());
			ITargetingInterface::Execute_DisplayLockedOnWidget(lockedOnActor, true);
		}
	}
}

void UTargetingComponent::OrientCamera()
{
	playerController->GetCharacterMovement()->bOrientRotationToMovement = false;
	playerController->GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void UTargetingComponent::LookAtTarget()
{
	auto xRot = playerController->GetController()->GetControlRotation().Roll;
	auto interp = FMath::RInterpConstantTo(playerController->GetController()->GetControlRotation(),
	                                       UKismetMathLibrary::FindLookAtRotation(
		                                       playerController->GetActorLocation(),
		                                       lockedOnActor->GetActorLocation() - FVector(0.0, 0.0, 135.0)),
	                                       GetWorld()->GetTimeSeconds(), 120.0);
	playerController->GetController()->SetControlRotation(FRotator(interp.Pitch, interp.Yaw, xRot));
}
