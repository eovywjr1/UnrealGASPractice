// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/ABCharacterPlayer.h"
#include "ABGASCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AABGASCharacterPlayer : public AABCharacterPlayer, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AABGASCharacterPlayer();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override final { return AbilitySystemComponent; }
	
	virtual void PossessedBy(AController* NewController) override final;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override final;
	
private:
	void SetupGASInputComponent();
	void GASInputPressed(int32 InInputID);
	void GASInputReleased(int32 InInputID);
	
	UFUNCTION()
	void OnOutOfHealth();
	
private:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbility>> Abilities;
	
	UPROPERTY(EditAnywhere, Category = "GAS")
	TMap<int32, TSubclassOf<class UGameplayAbility>> InputAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TObjectPtr<class UABGASWidgetComponent> HpBar;
};
