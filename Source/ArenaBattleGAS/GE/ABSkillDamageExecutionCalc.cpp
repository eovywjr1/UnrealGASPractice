// Fill out your copyright notice in the Description page of Project Settings.


#include "GE/ABSkillDamageExecutionCalc.h"

#include "AbilitySystemComponent.h"
#include "Attribute/ABCharacterAttributeSet.h"
#include "Attribute/ABCharacterSkillAttributeSet.h"

void UABSkillDamageExecutionCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent(); 
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	
	if(SourceAbilitySystemComponent && TargetAbilitySystemComponent)
	{
		AActor* SourceActor = SourceAbilitySystemComponent->GetAvatarActor();
		AActor* TargetActor = TargetAbilitySystemComponent->GetAvatarActor();
		
		if( SourceActor && TargetActor )
		{
			const float MaxDamageRange = SourceAbilitySystemComponent->GetNumericAttributeBase(UABCharacterSkillAttributeSet::GetSkillRangeAttribute());
			const float MaxDamage = SourceAbilitySystemComponent->GetNumericAttributeBase(UABCharacterSkillAttributeSet::GetSkillRateAttribute());
			const float Distance = FMath::Clamp(SourceActor->GetDistanceTo(TargetActor), 0, MaxDamageRange);
			const float InverseDamageRatio = 1.0f - Distance/MaxDamageRange;
			const float Damage = InverseDamageRatio * MaxDamage;
			
			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UABCharacterAttributeSet::GetDamageAttribute(), EGameplayModOp::Additive, Damage));
		}
	} 
}
