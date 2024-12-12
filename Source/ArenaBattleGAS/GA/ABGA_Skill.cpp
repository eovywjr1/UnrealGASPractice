// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/ABGA_Skill.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/ABGASCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

UABGA_Skill::UABGA_Skill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UABGA_Skill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AABGASCharacterPlayer* Character = Cast<AABGASCharacterPlayer>(ActorInfo->AvatarActor.Get());
	if (Character == nullptr)
	{
		return;
	}

	SkillActionMontage = Character->GetSkillActionMontage();
	if (SkillActionMontage == nullptr)
	{
		return;
	}

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), SkillActionMontage, 1.0f);
	PlayAttackTask->OnCompleted.AddDynamic(this, &UABGA_Skill::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this, &UABGA_Skill::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();
}

void UABGA_Skill::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get()))
	{
		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UABGA_Skill::OnCompleteCallback()
{
	bool bReplicateEndAbility = false;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UABGA_Skill::OnInterruptedCallback()
{
	bool bReplicateEndAbility = false;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
