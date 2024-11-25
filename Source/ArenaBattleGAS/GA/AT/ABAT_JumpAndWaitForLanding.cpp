// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/AT/ABAT_JumpAndWaitForLanding.h"

#include "GameFramework/Character.h"

UABAT_JumpAndWaitForLanding::UABAT_JumpAndWaitForLanding()
{}

UABAT_JumpAndWaitForLanding* UABAT_JumpAndWaitForLanding::CreateTask(UGameplayAbility* OwningAbility)
{
	UABAT_JumpAndWaitForLanding* NewTask = NewAbilityTask<UABAT_JumpAndWaitForLanding>(OwningAbility);
	return NewTask;
}

void UABAT_JumpAndWaitForLanding::Activate()
{
	Super::Activate();

	ACharacter* Avatar = CastChecked<ACharacter>(GetAvatarActor());
	Avatar->LandedDelegate.AddDynamic(this, &ThisClass::OnLandedCallback);
	Avatar->Jump();

	SetWaitingOnAvatar();
}

void UABAT_JumpAndWaitForLanding::OnDestroy(bool bInOwnerFinished)
{
	ACharacter* Avatar = CastChecked<ACharacter>(GetAvatarActor());
	Avatar->LandedDelegate.RemoveDynamic(this, &ThisClass::OnLandedCallback);

	Super::OnDestroy(bInOwnerFinished);
}

void UABAT_JumpAndWaitForLanding::OnLandedCallback(const FHitResult& Hit)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast();
	}
}
