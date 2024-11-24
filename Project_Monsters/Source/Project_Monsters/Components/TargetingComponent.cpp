// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingComponent.h"

#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_Monsters/CharacterControllerComponent/PlayerCharacterController.h"

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
void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTargetingComponent::FindActorsToLockOnTo()
{
	auto traceStart = playerController->GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));
	FHitResult hitResult;
	TArray<AActor*> actorsToIgnore;

	if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), traceStart, traceStart, radius, ObjectTypesArray, false, actorsToIgnore, EDrawDebugTrace::None, hitResult, true))
	{
		
	}

}

