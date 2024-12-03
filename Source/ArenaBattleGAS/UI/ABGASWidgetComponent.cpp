// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABGASWidgetComponent.h"

#include "ABGASUserWidget.h"

void UABGASWidgetComponent::InitWidget()
{
	Super::InitWidget();

	if (UABGASUserWidget* GASUserWidget = Cast<UABGASUserWidget>(GetWidget()))
	{
		GASUserWidget->SetAbilitySystemComponent(GetOwner());
	}
}
