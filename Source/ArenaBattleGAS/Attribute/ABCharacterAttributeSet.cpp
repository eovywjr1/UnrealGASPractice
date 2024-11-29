// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/ABCharacterAttributeSet.h"

UABCharacterAttributeSet::UABCharacterAttributeSet()
	: AttackRange(100.0f),
	  MaxAttackRange(300.0f),
	  AttackRadius(50.0f),
	  MaxAttackRadius(150.0f),
	  AttackRate(30.0f),
	  MaxAttackRate(100.0f),
	  MaxHealth(100.0f)
{
	InitHealth(GetMaxHealth());
}

void UABCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void UABCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{}