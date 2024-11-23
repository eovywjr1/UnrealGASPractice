// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABGASCharacterPlayer.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Player/ABGASPlayerState.h"

AABGASCharacterPlayer::AABGASCharacterPlayer()
	: AABCharacterPlayer()
{
	AbilitySystemComponent = nullptr;
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ArenaBattleGAS/Animation/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}
}

void AABGASCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AABGASPlayerState* CharacterPlayerState = GetPlayerState<AABGASPlayerState>())
	{
		AbilitySystemComponent = CharacterPlayerState->GetAbilitySystemComponent();
		AbilitySystemComponent->InitAbilityActorInfo(CharacterPlayerState, this);

		for (const TSubclassOf<UGameplayAbility>& Ability : Abilities)
		{
			FGameplayAbilitySpec AbilitySpec(Ability);
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
		
		for (const auto& InputAbility : InputAbilities)
		{
			FGameplayAbilitySpec AbilitySpec(InputAbility.Value);
			AbilitySpec.InputID = InputAbility.Key;
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
		
		APlayerController* PlayerController = CastChecked<APlayerController>(NewController);
		PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));
	}
}

void AABGASCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	SetupGASInputComponent();
}

void AABGASCharacterPlayer::SetupGASInputComponent()
{
	if (IsValid(AbilitySystemComponent) == false || InputComponent == nullptr)
	{
		return;
	}

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AABGASCharacterPlayer::GASInputPressed, 0);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AABGASCharacterPlayer::GASInputReleased, 0);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AABGASCharacterPlayer::GASInputPressed, 1);
}

void AABGASCharacterPlayer::GASInputPressed(int32 InInputID)
{
	if (FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromInputID(InInputID))
	{
		AbilitySpec->InputPressed = true;

		if (AbilitySpec->IsActive())
		{
			AbilitySystemComponent->AbilitySpecInputPressed(*AbilitySpec);
		}
		else
		{
			AbilitySystemComponent->TryActivateAbility(AbilitySpec->Handle);
		}
	}
}

void AABGASCharacterPlayer::GASInputReleased(int32 InInputID)
{
	if (FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromInputID(InInputID))
	{
		AbilitySpec->InputPressed = false;

		if (AbilitySpec->IsActive())
		{
			AbilitySystemComponent->AbilitySpecInputReleased(*AbilitySpec);
		}
	}
}
