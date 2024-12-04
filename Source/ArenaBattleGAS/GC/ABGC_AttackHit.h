// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "ABGC_AttackHit.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABGC_AttackHit : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
	
private:
	UABGC_AttackHit();
	
	bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override final;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TObjectPtr<class UParticleSystem> ParticleSystem;
	
};
