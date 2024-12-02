// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/ABCharacterAttributeSet.h"

#include "GameplayEffectExtension.h"

UABCharacterAttributeSet::UABCharacterAttributeSet()
	: AttackRange(100.0f),
	  MaxAttackRange(300.0f),
	  AttackRadius(50.0f),
	  MaxAttackRadius(150.0f),
	  AttackRate(30.0f),
	  MaxAttackRate(100.0f),
	  MaxHealth(100.0f),
	  Damage(0.0f)
{
	InitHealth(GetMaxHealth());
}

void UABCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	constexpr float MinimumHealth = 0.0f;
	
	if (Data.EvaluatedData.Attribute == GetDamageAttribute()) 
	{
		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), MinimumHealth, GetMaxHealth()));
		SetDamage(0.0f);
	}
}
