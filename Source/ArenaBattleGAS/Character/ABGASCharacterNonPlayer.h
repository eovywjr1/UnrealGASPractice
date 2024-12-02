// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/ABCharacterNonPlayer.h"
#include "ABGASCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AABGASCharacterNonPlayer : public AABCharacterNonPlayer, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
private:
	AABGASCharacterNonPlayer();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override final { return AbilitySystemComponent; }
	virtual void PossessedBy(AController* NewController) override final;
	
private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<class UABCharacterAttributeSet> AttributeSet;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<class UGameplayEffect> InitStatEffect;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	float Level = 1.0f;
};
