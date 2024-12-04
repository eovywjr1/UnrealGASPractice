// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ABGASItemBox.h"
#include "ABGASWeaponBox.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AABGASWeaponBox : public AABGASItemBox
{
	GENERATED_BODY()

private:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override final;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true, Categories=Event))
	FGameplayTag WeaponEventTag;
};
