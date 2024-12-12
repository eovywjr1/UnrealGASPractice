// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ABGA_Skill.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABGA_Skill : public UGameplayAbility
{
	GENERATED_BODY()
	
private:
	UABGA_Skill();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override final;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override final;
	
	UFUNCTION()
	void OnCompleteCallback();
	
	UFUNCTION()
	void OnInterruptedCallback();
	
private:
	UPROPERTY()
	TObjectPtr<class UAnimMontage> SkillActionMontage = nullptr;
};
