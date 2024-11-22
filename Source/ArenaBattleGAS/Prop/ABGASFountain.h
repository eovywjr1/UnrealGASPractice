// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/ABFountain.h"
#include "AbilitySystemInterface.h"
#include "ABGASFountain.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AABGASFountain : public AABFountain, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AABGASFountain();
	
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override final { return AbilitySystemComponent; }
	
private:
	virtual void PostInitializeComponents() override final;
	virtual void BeginPlay() override final;
	
	virtual void TimerAction();
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent; 
	
	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbility>> Abilities;
	
	UPROPERTY(VisibleAnywhere, Category = "Momvement")
	TObjectPtr<class URotatingMovementComponent> RotatingMovement;
	
	UPROPERTY(VisibleAnywhere, Category = "Timer")
	float ActionPeriod;
	
	FTimerHandle ActionTimer;
};
