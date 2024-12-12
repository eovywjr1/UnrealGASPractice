// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/ABGA_AttackHitCheck.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AT/ABAT_Trace.h"
#include "Attribute/ABCharacterAttributeSet.h"
#include "TA/ABTA_Trace.h"
#include "Tag/ABGamePlayTag.h"

UABGA_AttackHitCheck::UABGA_AttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UABGA_AttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CurrentComboLevel = TriggerEventData->EventMagnitude;

	UABAT_Trace* AttackTraceTask = UABAT_Trace::CreateTask(this, TargetActorClass);
	AttackTraceTask->OnComplete.AddDynamic(this, &ThisClass::OnTraceResultCallback);
	AttackTraceTask->ReadyForActivation();
}

void UABGA_AttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect, CurrentComboLevel);
		if (EffectSpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);

			FHitResult HitResult = *TargetDataHandle.Get(0)->GetHitResult();

			if (UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor()))
			{
				FGameplayEffectContextHandle EffectContextHandle = UAbilitySystemBlueprintLibrary::GetEffectContext(EffectSpecHandle);
				EffectContextHandle.AddHitResult(HitResult);
				FGameplayCueParameters CueParameters;
				CueParameters.EffectContext = EffectContextHandle;

				TargetAbilitySystemComponent->ExecuteGameplayCue(GAMEPLAYCUE_CHARCTER_ATTACKHIT, CueParameters);
			}
		}

		FGameplayEffectSpecHandle BuffEffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackBuffEffect, CurrentComboLevel);
		if (BuffEffectSpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, BuffEffectSpecHandle);
		}
	}
	else if (UAbilitySystemBlueprintLibrary::TargetDataHasActor(TargetDataHandle, 0))
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect, CurrentComboLevel);
		if (EffectSpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);
		}

		FGameplayEffectContextHandle EffectContextHandle = UAbilitySystemBlueprintLibrary::GetEffectContext(EffectSpecHandle);
		EffectContextHandle.AddActors(TargetDataHandle.Get(0)->GetActors());
		FGameplayCueParameters CueParameters;
		CueParameters.EffectContext = EffectContextHandle;

		GetAbilitySystemComponentFromActorInfo_Checked()->ExecuteGameplayCue(GAMEPLAYCUE_CHARCTER_ATTACKHIT, CueParameters);
	}

	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
