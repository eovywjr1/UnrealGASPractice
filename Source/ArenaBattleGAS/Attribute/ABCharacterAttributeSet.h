// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ABCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
	friend class UABGE_AttackDamage;
	
private:
	UABCharacterAttributeSet();
	
public:
	ATTRIBUTE_ACCESSORS(UABCharacterAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS(UABCharacterAttributeSet, MaxAttackRange);
	ATTRIBUTE_ACCESSORS(UABCharacterAttributeSet, AttackRadius);
	ATTRIBUTE_ACCESSORS(UABCharacterAttributeSet, MaxAttackRadius);
	ATTRIBUTE_ACCESSORS(UABCharacterAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(UABCharacterAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS(UABCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UABCharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UABCharacterAttributeSet, Damage);
	
private:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data);

private:
	UPROPERTY(EditAnywhere, Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData AttackRange;
	
	UPROPERTY(EditAnywhere, Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxAttackRange;
	
	UPROPERTY(EditAnywhere, Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData AttackRadius;
	
	UPROPERTY(EditAnywhere, Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxAttackRadius;
	
	UPROPERTY(EditAnywhere, Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData AttackRate;
	
	UPROPERTY(EditAnywhere, Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxAttackRate;
	
	UPROPERTY(EditAnywhere, Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Health;
	
	UPROPERTY(EditAnywhere, Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(EditAnywhere, Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Damage;
};
