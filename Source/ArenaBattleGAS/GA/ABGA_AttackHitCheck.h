// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ABGA_AttackHitCheck.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABGA_AttackHitCheck : public UGameplayAbility
{
	GENERATED_BODY()

private:
	UABGA_AttackHitCheck();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override final;
	
	UFUNCTION()
	void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> AttackDamageEffect;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> AttackBuffEffect;
	
	float CurrentComboLevel = 0.0f;
	
	UPROPERTY(EditDefaultsOnly , meta=(AllowPrivateAccess=true))
	TSubclassOf<class AABTA_Trace> TargetActorClass = nullptr;
};
