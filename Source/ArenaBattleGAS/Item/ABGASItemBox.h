// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "ABGASItemBox.generated.h"

UCLASS()
class ARENABATTLEGAS_API AABGASItemBox : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	AABGASItemBox();

	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override final { return AbilitySystemComponent; };
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	virtual void PostInitializeComponents() override final;

private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<class UBoxComponent> Trigger;

	UPROPERTY()
	TObjectPtr<class UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	TSubclassOf<class UGameplayEffect> GameplayEffectClass;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true, Categories=GameplayCue))
	FGameplayTag GameplayCueTag;
};
