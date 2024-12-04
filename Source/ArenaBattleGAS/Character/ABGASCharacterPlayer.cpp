// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABGASCharacterPlayer.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Attribute/ABCharacterAttributeSet.h"
#include "Player/ABGASPlayerState.h"
#include "Tag/ABGamePlayTag.h"
#include "UI/ABGASWidgetComponent.h"

AABGASCharacterPlayer::AABGASCharacterPlayer()
	: AABCharacterPlayer()
{
	AbilitySystemComponent = nullptr;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ArenaBattleGAS/Animation/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}

	HpBar = CreateDefaultSubobject<UABGASWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Game/ArenaBattle/UI/WBP_HpBar.WBP_HpBar_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(200.0f, 20.0f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blunt/Blunt_Hellhammer/SK_Blunt_HellHammer.SK_Blunt_HellHammer'"));
	if (WeaponMeshRef.Object)
	{
		WeaponMesh = WeaponMeshRef.Object;
	}

	WeaponRange = 75.0f;
	WeaponAttackRate = 100.0f;
}

void AABGASCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AABGASPlayerState* CharacterPlayerState = GetPlayerState<AABGASPlayerState>())
	{
		AbilitySystemComponent = CharacterPlayerState->GetAbilitySystemComponent();
		AbilitySystemComponent->InitAbilityActorInfo(CharacterPlayerState, this);
		if (const UABCharacterAttributeSet* CurrentAttributeSet = AbilitySystemComponent->GetSet<UABCharacterAttributeSet>())
		{
			CurrentAttributeSet->OnOutOfHealth.AddDynamic(this, &ThisClass::OnOutOfHealth);
		}

		AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(EVENT_CHARACTER_WEAPON_EQUIP).AddUObject(this, &ThisClass::EquipWeapon);
		AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(EVENT_CHARACTER_WEAPON_UNEQUIP).AddUObject(this, &ThisClass::UnEquipWeapon);


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

void AABGASCharacterPlayer::OnOutOfHealth()
{
	SetDead();
}

void AABGASCharacterPlayer::EquipWeapon(const FGameplayEventData* EventData)
{
	if (Weapon)
	{
		Weapon->SetSkeletalMesh(WeaponMesh);
		
		// 수동으로 어트리뷰트에 접근하는 것은 바람직하지 않지만 일부러 구현
		const float CurrentAttackRange = AbilitySystemComponent->GetNumericAttributeBase(UABCharacterAttributeSet::GetAttackRangeAttribute());
		const float CurrentAttackRate = AbilitySystemComponent->GetNumericAttributeBase(UABCharacterAttributeSet::GetAttackRateAttribute());
		
		AbilitySystemComponent->SetNumericAttributeBase(UABCharacterAttributeSet::GetAttackRangeAttribute(), CurrentAttackRange + WeaponRange);
		AbilitySystemComponent->SetNumericAttributeBase(UABCharacterAttributeSet::GetAttackRateAttribute(), CurrentAttackRate + WeaponAttackRate);
	}
}

void AABGASCharacterPlayer::UnEquipWeapon(const FGameplayEventData* EventData)
{
	if (Weapon)
	{
		Weapon->SetSkeletalMesh(nullptr);
		
		// 수동으로 어트리뷰트에 접근하는 것은 바람직하지 않지만 일부러 구현
		const float CurrentAttackRange = AbilitySystemComponent->GetNumericAttributeBase(UABCharacterAttributeSet::GetAttackRangeAttribute());
		const float CurrentAttackRate = AbilitySystemComponent->GetNumericAttributeBase(UABCharacterAttributeSet::GetAttackRateAttribute());
		
		AbilitySystemComponent->SetNumericAttributeBase(UABCharacterAttributeSet::GetAttackRangeAttribute(), CurrentAttackRange - WeaponRange);
		AbilitySystemComponent->SetNumericAttributeBase(UABCharacterAttributeSet::GetAttackRateAttribute(), CurrentAttackRate - WeaponAttackRate);
	}
}
