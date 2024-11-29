// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include <GameplayEffectTypes.h>
#include "AbilitySystemInterface.h"
#include "Project_Monsters/Attributes/TheHuntAttributeSet.h"
#include "PlayerCharacterController.generated.h"

class UTargetingComponent;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UTheHuntGameInstance;
struct FInputActionValue;

UCLASS()
class PROJECT_MONSTERS_API APlayerCharacterController : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerCharacterController();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void InitializeAttributes();
	virtual void GiveDefaultAbilities();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
	int MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
	int MaxStamina = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
	int MaxStat = 99;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> defaultAbilities;
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Jump() override; 
	virtual void Landed(const FHitResult& Hit) override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	FTimerHandle staminaTimerHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Stats", meta=(AllowPrivateAccess=true))
	UTheHuntGameInstance* gameInstance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputMappingContext* mappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/PlayerController/Input/IMC_Default.IMC_Default'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* jumpAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Jump.IA_Jump'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lookAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Look.IA_Look'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lockOnAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_LockOn.IA_LockOn'"));;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lockOnActionLeft = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_NextTargetLeft.IA_NextTargetLeft'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* lockOnActionRight = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_NextTargetRight.IA_NextTargetRight'"));
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* moveAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Move.IA_Move'"));;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* sprintAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerController/Input/Actions/IA_Sprint.IA_Sprint'"));;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UCameraComponent* cameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UAbilitySystemComponent* abilitySystemComponent;
	UPROPERTY()
	UTheHuntAttributeSet* attributes;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	USpringArmComponent* springArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UTargetingComponent* targetingComponent;

	UPROPERTY(EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> playerHudClass;
	UPROPERTY()
	class UPlayerHud* playerHud;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment", meta=(AllowPrivateAccess=true))
	TSubclassOf<class AEquipment> leftHandEquipment = LoadObject<UClass>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Weapons/bp_HunterPistol_C.bp_HunterPistol_C'")); 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment", meta=(AllowPrivateAccess=true))
	TSubclassOf<AEquipment> rightHandEquipment = LoadObject<UClass>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Weapons/bp_Sickle_C.bp_Sickle_C'")); ;
	
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void StopSprint();
	void Stamina(bool Sprinting, bool ReachedZero);
	void RechargeStamina();
	void AddEquipment(FName SocketName, UClass* Equipment);
};
