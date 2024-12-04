// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacterController.generated.h"

struct FGameplayTagContainer;
class UTheHuntAttributeSet;

UCLASS()
class PROJECT_MONSTERS_API ABaseCharacterController : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacterController();
	void AddEquipment(FName SocketName, UClass* Equipment) const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void InitializeAttributes();
	virtual void GiveDefaultAbilities();

	UFUNCTION(BlueprintCallable, Category="Attributes")
	virtual int32 GetCharacterLevel() const;
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

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ActivateAbilitiesWithTag(FGameplayTagContainer AbilityTags, bool AllowRemoteActivation = true);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> defaultAbilities;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	UAbilitySystemComponent* abilitySystemComponent;
	UPROPERTY()
	UTheHuntAttributeSet* attributes;

protected:
	UPROPERTY(EditAnywhere, Category="Attributes")
	int32 characterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<class UGameplayEffect> defaultAttributeEffects;

	virtual void SetTestAbilities();
};
