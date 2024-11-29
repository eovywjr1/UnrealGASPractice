// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/ABGA_AttackHitCheck.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AT/ABAT_Trace.h"
#include "Attribute/ABCharacterAttributeSet.h"
#include "TA/ABTA_Trace.h"

UABGA_AttackHitCheck::UABGA_AttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UABGA_AttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UABAT_Trace* AttackTraceTask = UABAT_Trace::CreateTask(this, AABTA_Trace::StaticClass());
	AttackTraceTask->OnComplete.AddDynamic(this, &ThisClass::OnTraceResultCallback);
	AttackTraceTask->ReadyForActivation();
}

void UABGA_AttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
		UAbilitySystemComponent* SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
		UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());

		if (SourceAbilitySystemComponent == nullptr || TargetAbilitySystemComponent == nullptr)
		{
			return;
		}

		// 원래는 게임플레이 이펙트로 어트리뷰트를 변경해야 하므로 임시로 const_cast 사용
		const UABCharacterAttributeSet* SourceAttributeSet = SourceAbilitySystemComponent->GetSet<UABCharacterAttributeSet>();
		UABCharacterAttributeSet* TargetAttributeSet = const_cast<UABCharacterAttributeSet*>(TargetAbilitySystemComponent->GetSet<UABCharacterAttributeSet>());

		if (SourceAttributeSet == nullptr || TargetAttributeSet == nullptr)
		{
			return;
		}

		TargetAttributeSet->SetHealth(TargetAttributeSet->GetHealth() - SourceAttributeSet->GetAttackRate());
	}

	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
