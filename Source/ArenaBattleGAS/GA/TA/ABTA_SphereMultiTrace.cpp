// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/TA/ABTA_SphereMultiTrace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Attribute/ABCharacterSkillAttributeSet.h"
#include "GameFramework/Character.h"
#include "Physics/ABCollision.h"

FGameplayAbilityTargetDataHandle AABTA_SphereMultiTrace::MakeTargetData() const
{
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);

	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (AbilitySystemComponent == nullptr)
	{
		return FGameplayAbilityTargetDataHandle();
	}

	const UABCharacterSkillAttributeSet* SkillAttributeSet = AbilitySystemComponent->GetSet<UABCharacterSkillAttributeSet>();
	if (SkillAttributeSet == nullptr)
	{
		return FGameplayAbilityTargetDataHandle();
	}

	TArray<FOverlapResult> Overlaps;
	const float SkillRadius = SkillAttributeSet->GetSkillRange();

	FVector Origin = Character->GetActorLocation();
	FCollisionQueryParams Params(SCENE_QUERY_STAT(AABTA_SphereMultiTrace), false, Character);
	GetWorld()->OverlapMultiByChannel(Overlaps, Origin, FQuat::Identity, CCHANNEL_ABACTION, FCollisionShape::MakeSphere(SkillRadius), Params);

	TArray<TWeakObjectPtr<AActor>> HitActors;
	for (const FOverlapResult& OverlapResult : Overlaps)
	{
		AActor* HitActor = OverlapResult.OverlapObjectHandle.FetchActor<AActor>();
		if (HitActor && HitActors.Contains(HitActor) == false)
		{
			HitActors.Add(HitActor);
		}
	}

	FGameplayAbilityTargetData_ActorArray* ActorsData = new FGameplayAbilityTargetData_ActorArray();
	ActorsData->SetActors(HitActors);

#ifdef ENABLE_DRAW_DEBUG
	if (bDrawDebug)
	{
		FColor DrawColor = HitActors.IsEmpty() ? FColor::Red : FColor::Green;
		DrawDebugSphere(GetWorld(), Origin, SkillRadius, 16, DrawColor, false, 5.0f);
	}
#endif

	return FGameplayAbilityTargetDataHandle(ActorsData);
}
