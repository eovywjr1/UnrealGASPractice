// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "ABTA_Trace.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AABTA_Trace : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	virtual void StartTargeting(UGameplayAbility* Ability) override final;

	UFUNCTION()
	virtual void ConfirmTargetingAndContinue() override final;

	void SetDrawDebug(bool InDrawDebug) { bDrawDebug = InDrawDebug; }

private:
	FGameplayAbilityTargetDataHandle MakeTargetData() const;
	bool bDrawDebug = false;
};
