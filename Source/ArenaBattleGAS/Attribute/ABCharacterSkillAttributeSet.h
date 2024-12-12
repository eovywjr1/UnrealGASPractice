// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ABCharacterSkillAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABCharacterSkillAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	ATTRIBUTE_ACCESSORS(UABCharacterSkillAttributeSet, SkillRange);
	ATTRIBUTE_ACCESSORS(UABCharacterSkillAttributeSet, MaxSkillRange);
	ATTRIBUTE_ACCESSORS(UABCharacterSkillAttributeSet, SkillRate);
	ATTRIBUTE_ACCESSORS(UABCharacterSkillAttributeSet, MaxSkillRate);
	ATTRIBUTE_ACCESSORS(UABCharacterSkillAttributeSet, SkillEnergy);
	ATTRIBUTE_ACCESSORS(UABCharacterSkillAttributeSet, MaxSkillEnergy);
	
private:
	UABCharacterSkillAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override final;
	
private:
	UPROPERTY()
	FGameplayAttributeData SkillRange;
	
	UPROPERTY()
	FGameplayAttributeData MaxSkillRange;
	
	UPROPERTY()
	FGameplayAttributeData SkillRate;
	
	UPROPERTY()
	FGameplayAttributeData MaxSkillRate;
	
	UPROPERTY()
	FGameplayAttributeData SkillEnergy;
	
	UPROPERTY()
	FGameplayAttributeData MaxSkillEnergy;
};
