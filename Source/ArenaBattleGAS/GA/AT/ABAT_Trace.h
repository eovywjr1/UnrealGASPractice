// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ABAT_Trace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABAT_Trace : public UAbilityTask
{
	GENERATED_BODY()
	
private:
	UABAT_Trace();
	
	virtual void Activate() override final;
	virtual void OnDestroy(bool bInOwnerFinished) override final;
	
public:
	static UABAT_Trace* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<class AABTA_Trace> TargetActorClass);
	
	void SpawnAndInitializeTargetActor();
	void FinalizeTargetActor();
	
private:
	void OnTargetDataRedayCallback(const FGameplayAbilityTargetDataHandle& DataHandle);
	
public:
	FTraceResultDelegate OnComplete;
	
private:
	UPROPERTY()
	TSubclassOf<class AABTA_Trace> TargetActorClass;
	
	UPROPERTY()
	TObjectPtr<class AABTA_Trace> SpawnedTargetActor;	
};
