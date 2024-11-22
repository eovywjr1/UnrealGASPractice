// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/ABGASFountain.h"

#include "ArenaBattleGAS.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Tag/ABGamePlayTag.h"
//#include "GA/ABGA_Rotate.h"

AABGASFountain::AABGASFountain()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotateMovement"));
	ActionPeriod = 3.0f;
}

void AABGASFountain::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// 액터가 초기화될 때 반드시 InitAbilityActorInfo 함수를 호출하여 AbilitySystemComponent를 초기화해야 함
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	// 처음부터 인스턴스를 생성하면 부하가 클 수 있기 때문에 기본적인 정보만 보유
	for (const TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
	// FGameplayAbilitySpec RotateSkillSpec(UABGA_Rotate::StaticClass());
	// AbilitySystemComponent->GiveAbility(RotateSkillSpec);

	RotatingMovement->bAutoActivate = false;
	RotatingMovement->Deactivate();
}

void AABGASFountain::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &AABGASFountain::TimerAction, ActionPeriod, true, 0.0f);
}

void AABGASFountain::TimerAction()
{
	ABGAS_LOG(LogABGAS, Log, TEXT("Begin"));

	FGameplayTagContainer TargetTag(ABTAG_ACTOR_ROTATE);

	if (AbilitySystemComponent->HasMatchingGameplayTag(ABTAG_ACTOR_ISROTATING) == false)
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag(TargetTag);
	}
	else
	{
		AbilitySystemComponent->CancelAbilities(&TargetTag);
	}

	// FGameplayAbilitySpec* RotateSpec = AbilitySystemComponent->FindAbilitySpecFromClass(UABGA_Rotate::StaticClass());
	// if (RotateSpec == nullptr)
	// {
	// 	ABGAS_LOG(LogABGAS, Log, TEXT("Rotate Spec Not Found"));
	// 	return;
	// }
	//
	// if (RotateSpec->IsActive() == false)
	// {
	// 	AbilitySystemComponent->TryActivateAbility(RotateSpec->Handle);
	// }
	// else
	// {
	// 	AbilitySystemComponent->CancelAbilityHandle(RotateSpec->Handle);
	// }
}
