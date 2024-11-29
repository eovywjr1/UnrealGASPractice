// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/TA/ABTA_Trace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbility.h"
#include "Attribute/ABCharacterAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Physics/ABCollision.h"

void AABTA_Trace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void AABTA_Trace::ConfirmTargetingAndContinue()
{
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
		TargetDataReadyDelegate.Broadcast(DataHandle);
	}
}

FGameplayAbilityTargetDataHandle AABTA_Trace::MakeTargetData() const
{
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);

	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (AbilitySystemComponent == nullptr)
	{
		return FGameplayAbilityTargetDataHandle();
	}

	const UABCharacterAttributeSet* AttributeSet = AbilitySystemComponent->GetSet<UABCharacterAttributeSet>();
	if (AttributeSet == nullptr)
	{
		return FGameplayAbilityTargetDataHandle();
	}
	
	FHitResult OutHitResult;
	const float AttackRange = AttributeSet->GetAttackRange();
	const float AttackRadius = AttributeSet->GetAttackRadius();

	FCollisionQueryParams Params(SCENE_QUERY_STAT(UABTA_Trace), false, Character);
	const FVector Forward = Character->GetActorForwardVector();
	const FVector Start = Character->GetActorLocation() + Forward * Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + Forward * AttackRange;

	bool bHitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_ABACTION, FCollisionShape::MakeSphere(AttackRadius), Params);

	FGameplayAbilityTargetDataHandle DataHandle;

	if (bHitDetected)
	{
		FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(OutHitResult);
		DataHandle.Add(TargetData);
	}

#if ENABLE_DRAW_DEBUG
	if (bDrawDebug)
	{
		const FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
		const float CapsuleHalfHeight = AttackRange * 0.5f;
		const FColor DrawColor = bHitDetected ? FColor::Green : FColor::Red;

		DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Forward).ToQuat(), DrawColor);
	}
#endif

	return DataHandle;
}
