// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameFramework/Character.h"
#include "Project_Monsters/Equipment/Equipment.h"
#include "BaseCharacterController.generated.h"

struct FGameplayTagContainer;
class UTheHuntAttributeSet;

UCLASS()
class PROJECT_MONSTERS_API ABaseCharacterController : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacterController();
	AEquipment* AddEquipment(FName SocketName, UClass* Equipment) const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	void SetAttributeValues();
	virtual void InitializeAttributes();
	virtual void GiveDefaultAbilities();
	// Attribute Functions
	virtual void HandleHealthChange(int32 DeltaValue, AActor* OtherActor);
	virtual void HandleStaminaChange(float DeltaValue, AActor* OtherActor);
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChange(int32 DeltaValue, AActor* OtherActor);
	UFUNCTION(BlueprintImplementableEvent)
	void OnStaminaChange(float DeltaValue, AActor* OtherActor);
	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();
	UFUNCTION(BlueprintCallable)
	bool ActivateMeleeAbility(bool AllowRemoteActivation);

	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetCharacterLevel();
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetVigor() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetMaxVigor() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetEndurance() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetMaxEndurance() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetStrength() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetMaxStrength() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetDexterity() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetMaxDexterity() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetBloodLust() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetMaxBloodLust() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetArcane() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetMaxArcane() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetBloodVials() const;
	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetMaxBloodVials() const;

	virtual int CalculateStrengthOutput(TEnumAsByte<EScaling> Strength);
	virtual int CalculateDexterityOutput(TEnumAsByte<EScaling> Dexterity);
	virtual int CalculateArcaneOutput(TEnumAsByte<EScaling> Arcane);

	virtual int32 CalculateMaxHealth(int Vigor) const;
	virtual int32 CalculateMaxStamina(int Endurance) const;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ActivateAbilitiesWithTag(FGameplayTagContainer AbilityTags, bool AllowRemoteActivation = true);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> defaultAbilities;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UAbilitySystemComponent* abilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UTheHuntAttributeSet* attributes;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Attributes")
	int32 characterLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attributes")
	int32 vigorLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attributes")
	int32 enduranceLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attributes")
	int32 strengthLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attributes")
	int32 dexterityLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attributes")
	int32 bloodLustLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attributes")
	int32 arcaneLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attributes")
	int32 health;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attributes")
	int32 maxHealth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attributes")
	float stamina;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attributes")
	float maxStamina;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<class UGameplayEffect> defaultAttributeEffects;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<class UGameplayEffect> vigorAttributeEffects;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<class UGameplayEffect> enduranceAttributeEffects;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<class UGameplayEffect> strengthAttributeEffects;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<class UGameplayEffect> dexterityAttributeEffects;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<class UGameplayEffect> bloodLustAttributeEffects;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<class UGameplayEffect> arcaneAttributeEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes | Melee")
	TSubclassOf<UGameplayAbility> meleeAbility;

	UPROPERTY()
	FGameplayAbilitySpecHandle meleeAbilitySpecHandle;

	virtual void SetMeleeAbility();
	
	virtual void SetTestAbilities();
};
