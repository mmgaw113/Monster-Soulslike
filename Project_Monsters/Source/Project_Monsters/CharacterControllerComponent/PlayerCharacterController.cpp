// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_Monsters/Components/TargetingComponent.h"

// Sets default values
APlayerCharacterController::APlayerCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	springArmComponent->SetupAttachment(RootComponent);
	springArmComponent->TargetArmLength = 400.0f; 	
	springArmComponent->bUsePawnControlRotation = true; 
	
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	cameraComponent->SetupAttachment(springArmComponent, USpringArmComponent::SocketName); 
	cameraComponent->bUsePawnControlRotation = false;

	targetingComponent = CreateDefaultSubobject<UTargetingComponent>("TargetingComponent");
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(mappingContext, 0);
		}
	}
}

void APlayerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Move);
		EnhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Look);
		EnhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Sprint);
		EnhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Canceled, this, &APlayerCharacterController::StopSprint);
		EnhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Completed, this, &APlayerCharacterController::StopSprint);
	}
}

void APlayerCharacterController::Look(const FInputActionValue& value)
{
	FVector2D LookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacterController::Move(const FInputActionValue& value)
{
	FVector2D MovementVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacterController::Sprint(const FInputActionValue& value)
{
	bool Sprinting = value.Get<bool>();

	if (Sprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	}
}

void APlayerCharacterController::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
}
