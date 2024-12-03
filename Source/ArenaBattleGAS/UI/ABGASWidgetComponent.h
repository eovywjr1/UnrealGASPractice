// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ABGASWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABGASWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
private:
	virtual void InitWidget() override final;
};
