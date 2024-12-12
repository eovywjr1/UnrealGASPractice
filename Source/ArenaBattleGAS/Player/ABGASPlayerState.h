// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "ABGASPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AABGASPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AABGASPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override final { return AbilitySystemComponent; }
	
private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<class UABCharacterAttributeSet> AttributeSet;
	
	UPROPERTY()
    TObjectPtr<class UABCharacterSkillAttributeSet> SkillAttributeSet;
};
