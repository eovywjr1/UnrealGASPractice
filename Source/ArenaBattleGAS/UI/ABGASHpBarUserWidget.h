// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ABGASUserWidget.h"
#include "GameplayEffectTypes.h"
#include "ABGASHpBarUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABGASHpBarUserWidget : public UABGASUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void SetAbilitySystemComponent(AActor* InOwner) override final;
	void OnHealthChanged(const FOnAttributeChangeData& ChangeData);
	void OnMaxHealthChanged(const FOnAttributeChangeData& ChangeData);
	void OnInvinsibleTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	void UpdateHpBar();
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PbHpBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TxtHpStat;
	
	float CurrentHealth = 0.0f;
	float CurrentMaxHealth = 0.1f; // CurrentMaxHealth로 나누기 때문에 안전하게 0이 아닌 수로 초기화
};
