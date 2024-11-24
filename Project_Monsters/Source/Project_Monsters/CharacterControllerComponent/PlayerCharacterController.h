// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterController.generated.h"

class UTargetingComponent;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class PROJECT_MONSTERS_API APlayerCharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacterController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputMappingContext* mappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/PlayerController/Input/IMC_Default.IMC_Default'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* jumpAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Jump.IA_Jump'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lookAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Look.IA_Look'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lockOnAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_LockOn.IA_LockOn'"));;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* moveAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Move.IA_Move'"));;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* sprintAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Sprint.IA_Sprint'"));;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UCameraComponent* cameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	USpringArmComponent* springArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UTargetingComponent* targetingComponent;
	
	void Look(const FInputActionValue& value);
	void Move(const FInputActionValue& value);
	void Sprint(const FInputActionValue& value);
	void StopSprint();
};
