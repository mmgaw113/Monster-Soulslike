// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "BaseCharacterController.h"
#include "PlayerCharacterController.generated.h"

class UTargetingComponent;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UTheHuntGameInstance;
struct FInputActionValue;

UCLASS()
class PROJECT_MONSTERS_API APlayerCharacterController : public ABaseCharacterController
{
	GENERATED_BODY()

public:
	APlayerCharacterController();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Landed(const FHitResult& Hit) override;

public:
	void CreateLevelUpScreen();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> playerHudClass;
	UPROPERTY()
	class UPlayerHud* playerHud;
	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> levelUpScreenClass;
	UPROPERTY()
	UUserWidget* levelUpScreen;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Animation")
	float primaryWeight = 1.0f;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Animation")
	float secondaryWeight = 1.0f;
	
private:
	FTimerHandle staminaTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats", meta=(AllowPrivateAccess=true))
	UTheHuntGameInstance* gameInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputMappingContext* mappingContext = LoadObject<UInputMappingContext>(
		nullptr,
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/PlayerController/Input/IMC_Default.IMC_Default'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* interactAction = LoadObject<UInputAction>(
		nullptr,
		TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Interact.IA_Interact'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* jumpAction = LoadObject<UInputAction>(
		nullptr, TEXT(
			"/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_JumpAction.IA_JumpAction'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lookAction = LoadObject<UInputAction>(
		nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Look.IA_Look'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lockOnAction = LoadObject<UInputAction>(
		nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_LockOn.IA_LockOn'"));;
	UInputAction* lockOnActionController = LoadObject<UInputAction>(
		nullptr, TEXT(
			"/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_NextTargetController.IA_NextTargetController'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lockOnActionLeft = LoadObject<UInputAction>(
		nullptr, TEXT(
			"/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_NextTargetLeft.IA_NextTargetLeft'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lockOnActionRight = LoadObject<UInputAction>(
		nullptr, TEXT(
			"/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_NextTargetRight.IA_NextTargetRight'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* meleeAction = LoadObject<UInputAction>(
		nullptr, TEXT(
			"/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Melee.IA_Melee'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* moveAction = LoadObject<UInputAction>(
		nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Move.IA_Move'"));;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* sprintAction = LoadObject<UInputAction>(
		nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Sprint.IA_Sprint'"));;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UCameraComponent* cameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	USpringArmComponent* springArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UTargetingComponent* targetingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment", meta=(AllowPrivateAccess=true))
	TSubclassOf<class AEquipment> leftHandEquipment = LoadObject<UClass>(
		nullptr, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Weapons/bp_HunterPistol_C.bp_HunterPistol_C'"));
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment", meta=(AllowPrivateAccess=true))
	TSubclassOf<AEquipment> rightHandEquipment = LoadObject<UClass>(
		nullptr, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Weapons/bp_Sickle_C.bp_Sickle_C'"));

	void Attack();
	void Interact();
	void Jumped(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void RechargeStamina();
	void Sprint(const FInputActionValue& Value);
	void StopSprint();
	void Stamina(bool Sprinting, bool ReachedZero);

	UFUNCTION(BlueprintCallable)
	void AttackFinished();

	UFUNCTION(BlueprintCallable)
	void Landed();
	
	UFUNCTION(BlueprintCallable)
	void OnJump();

	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar() const;

	UFUNCTION(BlueprintCallable)
	void UpdateStaminaBar() const;
};
