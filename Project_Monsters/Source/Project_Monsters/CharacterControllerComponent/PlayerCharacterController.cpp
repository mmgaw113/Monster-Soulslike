// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_Monsters/UserInterface/PlayerHud.h"
#include "Project_Monsters/Components/TargetingComponent.h"

// Sets default Values
APlayerCharacterController::APlayerCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->JumpZVelocity = 450.f;
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

	gameInstance = Cast<UTheHuntGameInstance>(GetGameInstance());
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(mappingContext, 0);
		}
	}

	if (playerHudClass)
	{
		playerHud = CreateWidget<UPlayerHud>(GetWorld(), playerHudClass);
		check(playerHud);
		playerHud->AddToPlayerScreen();
	}
}

void APlayerCharacterController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (playerHud)
	{
		playerHud->RemoveFromParent();
		playerHud = nullptr;
	}

	Super::EndPlay(EndPlayReason);
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
		//Basic Movement
		EnhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Started, this, &APlayerCharacterController::Jump);
		EnhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Move);
		EnhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Look);
		EnhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Sprint);
		EnhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Canceled, this, &APlayerCharacterController::StopSprint);
		EnhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Completed, this, &APlayerCharacterController::StopSprint);

		//Targeting Enemies
		EnhancedInputComponent->BindAction(lockOnAction, ETriggerEvent::Started, targetingComponent, &UTargetingComponent::LockOnToTarget);
		EnhancedInputComponent->BindAction(lockOnActionLeft, ETriggerEvent::Started, targetingComponent, &UTargetingComponent::LockOnToTargetLeft);
		EnhancedInputComponent->BindAction(lockOnActionRight, ETriggerEvent::Started, targetingComponent, &UTargetingComponent::LockOnToTargetRight);
	}
}

void APlayerCharacterController::Jump()
{
	ACharacter::Jump();

	gameInstance->PlayerAttributes.CurrentStamina -= 15;
	playerHud->SetStamina(gameInstance->PlayerAttributes.CurrentStamina, gameInstance->PlayerAttributes.MaxStamina);

	if (GetWorldTimerManager().IsTimerActive(staminaTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(staminaTimerHandle);
	}
}

void APlayerCharacterController::Landed(const FHitResult& Hit)
{
	if (!GetWorldTimerManager().IsTimerActive(staminaTimerHandle))
	{
		GetWorldTimerManager().SetTimer(staminaTimerHandle, this, &APlayerCharacterController::RechargeStamina, 0.01f, true);
	}
}

void APlayerCharacterController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr && !targetingComponent->lockedOn)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacterController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

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

void APlayerCharacterController::Sprint(const FInputActionValue& Value)
{
	bool Sprinting = Value.Get<bool>();

	if (Sprinting && gameInstance->PlayerAttributes.CurrentStamina > 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 800.0f;
		playerHud->SetStamina(gameInstance->PlayerAttributes.CurrentStamina, gameInstance->PlayerAttributes.MaxStamina);
		Stamina(true, false);

		if (GetWorldTimerManager().IsTimerActive(staminaTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(staminaTimerHandle);
		}
	}
	else if (gameInstance->PlayerAttributes.CurrentStamina <= 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		Stamina(false, true);
	}
}

void APlayerCharacterController::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	Stamina(false, false);
}

void APlayerCharacterController::Stamina(bool Sprinting, bool ReachedZero)
{
	if (Sprinting && gameInstance->PlayerAttributes.CurrentStamina > 0)
	{
		gameInstance->PlayerAttributes.CurrentStamina -= 1;
	}
	else if (!Sprinting && !ReachedZero)
	{
		GetWorldTimerManager().SetTimer(staminaTimerHandle, this, &APlayerCharacterController::RechargeStamina, 0.01f, true);
	}
}

void APlayerCharacterController::RechargeStamina()
{
	if (gameInstance->PlayerAttributes.CurrentStamina <= gameInstance->PlayerAttributes.MaxStamina)
	{
		playerHud->SetStamina(gameInstance->PlayerAttributes.CurrentStamina, gameInstance->PlayerAttributes.MaxStamina);
		gameInstance->PlayerAttributes.CurrentStamina += 1;	
	}
	else
	{
		GetWorldTimerManager().ClearTimer(staminaTimerHandle);
	}
}

