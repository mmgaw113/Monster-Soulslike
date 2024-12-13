// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/SpringArmComponent.h"
#include "Project_Monsters/UserInterface/PlayerHud.h"
#include "Project_Monsters/Components/TargetingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Monsters/Equipment/Equipment.h"
#include "Project_Monsters/Interfaces/InteractableInterface.h"

// Sets default Values
APlayerCharacterController::APlayerCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(30.f, 90.0f);

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

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	gameInstance = Cast<UTheHuntGameInstance>(GetGameInstance());

	health = CalculateMaxHealth(vigorLevel);
	maxHealth = CalculateMaxHealth(vigorLevel);
	stamina = CalculateMaxStamina(enduranceLevel);
	maxStamina = CalculateMaxStamina(enduranceLevel);

	UsingGamepad();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
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

	secondaryWeapon = AddEquipment("LeftHandSocket", leftHandEquipment);
	primaryWeapon = AddEquipment("RightHandSocket", rightHandEquipment);
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

	MovingForward(MovementVector.Y);
	MovingRight(MovementVector.X);
}

void APlayerCharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Basic Movement
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this,
		                                   &APlayerCharacterController::Move);
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Canceled, this,
		                                   &APlayerCharacterController::ResetMovementVector);
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Completed, this,
		                                   &APlayerCharacterController::ResetMovementVector);
		EnhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this,
		                                   &APlayerCharacterController::Look);
		EnhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Triggered, this,
		                                   &APlayerCharacterController::Sprint);
		EnhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Canceled, this,
		                                   &APlayerCharacterController::StopSprint);
		EnhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Completed, this,
		                                   &APlayerCharacterController::StopSprint);
		EnhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Started, this,
		                                   &APlayerCharacterController::Jumped);
		EnhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Canceled, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(dodgeAction, ETriggerEvent::Completed, this,
		                                   &APlayerCharacterController::Dodge);
		// Interact
		EnhancedInputComponent->BindAction(interactAction, ETriggerEvent::Started, this,
		                                   &APlayerCharacterController::Interact);

		// Targeting Enemies
		EnhancedInputComponent->BindAction(lockOnAction, ETriggerEvent::Started, targetingComponent,
		                                   &UTargetingComponent::LockOnToTarget);
		EnhancedInputComponent->BindAction(lockOnActionLeft, ETriggerEvent::Started, targetingComponent,
		                                   &UTargetingComponent::LockOnToTargetLeft);
		EnhancedInputComponent->BindAction(lockOnActionRight, ETriggerEvent::Started, targetingComponent,
		                                   &UTargetingComponent::LockOnToTargetRight);

		// Melee and Perry
		EnhancedInputComponent->BindAction(meleeAction, ETriggerEvent::Started, this,
		                                   &APlayerCharacterController::Attack);
		EnhancedInputComponent->BindAction(heavyAttackAction, ETriggerEvent::Started, this,
		                                   &APlayerCharacterController::HeavyAttack);
	}
}

void APlayerCharacterController::Attack()
{
	if (stamina > 10.0f)
	{
		if (isFalling)
		{
			stamina -= 10.0f;
			UpdateStaminaBar();
			ActivateJumpMeleeAbility(true);
			primaryWeight = 0.0f;
			secondaryWeight = 0.0f;
		}
		else
		{
			stamina -= 10.0f;
			UpdateStaminaBar();
			ActivateMeleeAbility(true);
			primaryWeight = 0.0f;
			secondaryWeight = 0.0f;
		}

		if (GetWorldTimerManager().IsTimerActive(staminaTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(staminaTimerHandle);
		}
	}
}

void APlayerCharacterController::HeavyAttack()
{
	if (stamina < 20.0f)
	{
		return;
	}

	if (isFalling)
	{
		return;
	}
	
	stamina -= 20.0f;
	UpdateStaminaBar();
	ActivateMeleeAbility(true);
	primaryWeight = 0.0f;
	secondaryWeight = 0.0f;

	if (GetWorldTimerManager().IsTimerActive(staminaTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(staminaTimerHandle);
	}
}

void APlayerCharacterController::Dodge()
{
	if (stamina < 20)
	{
		return;
	}

	if (dodging)
	{
		return;
	}

	if (dodgeForward)
	{
		if (dodgeRight)
		{
			dodgeMontage = LoadObject<UAnimMontage>(nullptr, TEXT(
				                                        "/Script/Engine.AnimMontage'/Game/Animations/DodgeAndRoll/AM_RollForwardRight_Root_Montage.AM_RollForwardRight_Root_Montage'"));
		}
		else if (dodgeLeft)
		{
			dodgeMontage = LoadObject<UAnimMontage>(nullptr, TEXT(
				                                        "/Script/Engine.AnimMontage'/Game/Animations/DodgeAndRoll/AM_RollForwardLeft_Root_Montage.AM_RollForwardLeft_Root_Montage'"));
		}
		else
		{
			dodgeMontage = LoadObject<UAnimMontage>(nullptr, TEXT(
				                                        "/Script/Engine.AnimMontage'/Game/Animations/DodgeAndRoll/AM_RollForward_Root_Montage.AM_RollForward_Root_Montage'"));
		}
	}
	else if (dodgeBackward)
	{
		if (dodgeRight)
		{
			dodgeMontage = LoadObject<UAnimMontage>(nullptr, TEXT(
				                                        "/Script/Engine.AnimMontage'/Game/Animations/DodgeAndRoll/AM_RollBackwardRight_Root_Montage.AM_RollBackwardRight_Root_Montage'"));
		}
		else if (dodgeLeft)
		{
			dodgeMontage = LoadObject<UAnimMontage>(nullptr, TEXT(
				                                        "/Script/Engine.AnimMontage'/Game/Animations/DodgeAndRoll/AM_RollBackwardLeft_Root_Montage.AM_RollBackwardLeft_Root_Montage'"));
		}
		else
		{
			dodgeMontage = LoadObject<UAnimMontage>(nullptr, TEXT(
				                                        "/Script/Engine.AnimMontage'/Game/Animations/DodgeAndRoll/AM_RollBackward_Root_Montage.AM_RollBackward_Root_Montage'"));
		}
	}
	else if (dodgeLeft)
	{
		dodgeMontage = LoadObject<UAnimMontage>(nullptr, TEXT(
			                                        "/Script/Engine.AnimMontage'/Game/Animations/DodgeAndRoll/AM_RollLeft_Root_Montage.AM_RollLeft_Root_Montage'"));
	}
	else if (dodgeRight)
	{
		dodgeMontage = LoadObject<UAnimMontage>(nullptr, TEXT(
			                                        "/Script/Engine.AnimMontage'/Game/Animations/DodgeAndRoll/AM_RollRight_Root_Montage.AM_RollRight_Root_Montage'"));
	}
	else if (!isMoving && !isMovingRight)
	{
		dodgeMontage = LoadObject<UAnimMontage>(nullptr, TEXT(
			                                        "/Script/Engine.AnimMontage'/Game/Animations/DodgeAndRoll/AM_DodgeBackward_Root_Montage.AM_DodgeBackward_Root_Montage'"));
	}

	dodging = true;
	PlayAnimMontage(dodgeMontage);
	stamina -= 20.0f;
	UpdateStaminaBar();
	GetWorldTimerManager().SetTimer(dodgerTimer, this, &APlayerCharacterController::ResetDodge, 0.3f, false);
}

void APlayerCharacterController::AttackFinished()
{
	primaryWeight = 1.0f;
	secondaryWeight = 1.0f;

	if (!GetWorldTimerManager().IsTimerActive(staminaTimerHandle))
	{
		GetWorldTimerManager().SetTimer(staminaTimerHandle, this, &APlayerCharacterController::RechargeStamina, 0.01f,
		                                true, 0.5f);
	}
}

bool APlayerCharacterController::CanTakeDamage()
{
	return dodging;
}

void APlayerCharacterController::Jumped(const FInputActionValue& Value)
{
	if (stamina > 15.0f)
	{
		stamina -= 15.0f;
		UpdateStaminaBar();
		isFalling = true;
		Jump();

		if (GetWorldTimerManager().IsTimerActive(staminaTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(staminaTimerHandle);
		}
	}
}

void APlayerCharacterController::Landed(const FHitResult& Hit)
{
	isFalling = false;

	if (!GetWorldTimerManager().IsTimerActive(staminaTimerHandle))
	{
		GetWorldTimerManager().SetTimer(staminaTimerHandle, this, &APlayerCharacterController::RechargeStamina, 0.01f,
		                                true, 0.5f);
	}
}

void APlayerCharacterController::CreateLevelUpScreen()
{
	if (levelUpScreenClass)
	{
		levelUpScreen = CreateWidget<UUserWidget>(GetWorld(), levelUpScreenClass);
		check(levelUpScreen);
		levelUpScreen->AddToPlayerScreen();
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameAndUI());
	}
}

void APlayerCharacterController::OnJump()
{
	UpdateStaminaBar();
}

void APlayerCharacterController::ResetDodge()
{
	dodging = false;

	if (GetWorldTimerManager().IsTimerActive(dodgerTimer))
	{
		GetWorldTimerManager().ClearTimer(dodgerTimer);
	}
}

void APlayerCharacterController::Landed()
{
	GEngine->AddOnScreenDebugMessage(1, 3.0, FColor::Cyan, TEXT("Landed"));
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
	MovementVector = Value.Get<FVector2D>();

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

void APlayerCharacterController::Interact()
{
	TArray<AActor*> OverLappingActors;
	GetOverlappingActors(OverLappingActors);

	for (auto OverLappingActor : OverLappingActors)
	{
		if (OverLappingActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
		{
			IInteractableInterface::Execute_Interact(OverLappingActor);
		}

		break;
	}
}

void APlayerCharacterController::Sprint(const FInputActionValue& Value)
{
	bool Sprinting = Value.Get<bool>();

	if (!GetCharacterMovement()->Velocity.IsZero())
	{
		if (Sprinting && stamina > 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = 800.0f;
			Stamina(true, false);

			if (GetWorldTimerManager().IsTimerActive(staminaTimerHandle))
			{
				GetWorldTimerManager().ClearTimer(staminaTimerHandle);
			}
		}
		else if (stamina <= 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = 500.0f;
			Stamina(false, true);
		}
	}
}

void APlayerCharacterController::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	Stamina(false, false);
}

void APlayerCharacterController::Stamina(bool Sprinting, bool ReachedZero)
{
	if (Sprinting && stamina > 0)
	{
		HandleStaminaChange(0, nullptr);
		stamina -= 1.0f;
	}
	else if (!Sprinting && !ReachedZero)
	{
		GetWorldTimerManager().SetTimer(staminaTimerHandle, this, &APlayerCharacterController::RechargeStamina, 0.01f,
		                                true, 0.5f);
	}
}

void APlayerCharacterController::MovingForward(float Value)
{
	if (UsingGamepad())
	{
		if (Value > 25)
		{
			isMoving = true;
			dodgeForward = true;
			dodgeBackward = false;
		}
		else if (Value < -25)
		{
			isMoving = true;
			dodgeBackward = true;
			dodgeForward = false;
		}
		else
		{
			isMoving = false;
			dodgeForward = false;
			dodgeBackward = false;
		}
	}
	else
	{
		if (Value > 0)
		{
			isMoving = true;
			dodgeForward = true;
			dodgeBackward = false;
		}
		else if (Value < 0)
		{
			isMoving = true;
			dodgeBackward = true;
			dodgeForward = false;
		}
		else
		{
			isMoving = false;
			dodgeForward = false;
			dodgeBackward = false;
		}
	}
}


void APlayerCharacterController::MovingRight(float Value)
{
	if (UsingGamepad())
	{
		if (Value > 25)
		{
			isMovingRight = true;
			dodgeRight = true;
			dodgeLeft = false;
		}
		else if (Value < -25)
		{
			isMovingRight = true;
			dodgeLeft = true;
			dodgeRight = false;
		}
		else
		{
			isMovingRight = false;
			dodgeLeft = false;
			dodgeRight = false;
		}
	}
	else
	{
		if (Value > 0)
		{
			isMovingRight = true;
			dodgeRight = true;
			dodgeLeft = false;
		}
		else if (Value < 0)
		{
			isMovingRight = true;
			dodgeLeft = true;
			dodgeRight = false;
		}
		else
		{
			isMovingRight = false;
			dodgeLeft = false;
			dodgeRight = false;
		}
	}
}

void APlayerCharacterController::ResetMovementVector()
{
	MovementVector = FVector2D(0, 0);
	isMoving = false;
	isMovingRight = false;
	dodgeLeft = false;
	dodgeRight = false;
	dodgeForward = false;
	dodgeBackward = false;
}

bool APlayerCharacterController::UsingGamepad()
{
	UInputDeviceSubsystem* InputDeviceSubsystem = GetGameInstance()->GetEngine()->GetEngineSubsystem<
		UInputDeviceSubsystem>();

	if (InputDeviceSubsystem->GetMostRecentlyUsedHardwareDevice(GetPlatformUserId()).PrimaryDeviceType ==
		EHardwareDevicePrimaryType::Gamepad)
	{
		return true;
	}

	return false;
}

void APlayerCharacterController::RechargeStamina()
{
	if (stamina <= maxStamina)
	{
		HandleStaminaChange(0, nullptr);
		stamina += 0.35f;
	}
	else
	{
		GetWorldTimerManager().ClearTimer(staminaTimerHandle);
	}
}

void APlayerCharacterController::UpdateHealthBar() const
{
	playerHud->SetHealth(health, maxHealth);
}

void APlayerCharacterController::UpdateStaminaBar() const
{
	playerHud->SetStamina(stamina, maxStamina);
}
