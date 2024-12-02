// Fill out your copyright notice in the Description page of Project Settings.


#include "GE/ABGE_AttackDamage.h"

#include "Attribute/ABCharacterAttributeSet.h"

UABGE_AttackDamage::UABGE_AttackDamage() 
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	
	FGameplayModifierInfo HealthModifier;
	HealthModifier.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(UABCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UABCharacterAttributeSet, Health)));
	
	FScalableFloat DamageAmount(-30.0f);
	HealthModifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(DamageAmount);
	
	Modifiers.Add(HealthModifier);
}
