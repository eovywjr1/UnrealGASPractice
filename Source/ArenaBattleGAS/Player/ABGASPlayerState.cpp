// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABGASPlayerState.h"

#include "AbilitySystemComponent.h"
#include "Attribute/ABCharacterAttributeSet.h"

AABGASPlayerState::AABGASPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponet"));
	//AbilitySystemComponent->SetIsReplicated(true); // 네트워크 멀티플레이를 지원한다면 서버에서 클라이언트로 객체가 전송돼야 하므로 컴포넌트가 리플리케이션이 되도록 설정
	
	AttributeSet = CreateDefaultSubobject<UABCharacterAttributeSet>(TEXT("AttributeSet"));
}
