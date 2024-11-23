// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/ABGA_Rotate.h"

#include "GameFramework/RotatingMovementComponent.h"
#include "Tag/ABGamePlayTag.h"

UABGA_Rotate::UABGA_Rotate() {
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityTags.AddTag(ABTAG_ACTOR_ROTATE);
	ActivationOwnedTags.AddTag(ABTAG_ACTOR_ISROTATING);
}

void UABGA_Rotate::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (AActor* AvatarActor = ActorInfo->AvatarActor.Get())
	{
		if (UActorComponent* RotatingMovement = AvatarActor->GetComponentByClass(URotatingMovementComponent::StaticClass()))
		{
			RotatingMovement->Activate(true);
		}
	}
}

void UABGA_Rotate::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	
	if (AActor* AvatarActor = ActorInfo->AvatarActor.Get())
	{
		if (UActorComponent* RotatingMovement = AvatarActor->GetComponentByClass(URotatingMovementComponent::StaticClass()))
		{
			RotatingMovement->Deactivate();
		}
	}
}
