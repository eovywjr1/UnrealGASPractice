// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABGASCharacterNonPlayer.h"

#include "AbilitySystemComponent.h"
#include "Attribute/ABCharacterAttributeSet.h"

AABGASCharacterNonPlayer::AABGASCharacterNonPlayer() 
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UABCharacterAttributeSet>(TEXT("AttributeSet"));
}

void AABGASCharacterNonPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}
