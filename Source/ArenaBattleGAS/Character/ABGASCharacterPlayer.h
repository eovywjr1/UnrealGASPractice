// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/ABCharacterPlayer.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "ABGASCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AABGASCharacterPlayer : public AABCharacterPlayer, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AABGASCharacterPlayer();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override final { return AbilitySystemComponent; }

	virtual void PossessedBy(AController* NewController) override final;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override final;

	FORCEINLINE UAnimMontage* GetSkillActionMontage() const { return SkillActionMontage; }

private:
	void SetupGASInputComponent();
	void GASInputPressed(int32 InInputID);
	void GASInputReleased(int32 InInputID);

	UFUNCTION()
	void OnOutOfHealth();

	void EquipWeapon(const FGameplayEventData* EventData);
	void UnEquipWeapon(const FGameplayEventData* EventData);

private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbility>> Abilities;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TMap<int32, TSubclassOf<class UGameplayAbility>> InputAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TObjectPtr<class UABGASWidgetComponent> HpBar;

	// 시간 관계상 캐릭터에 선언하는 것, Weapon 객체를 따로 만들고 AttributeSet도 따로 만들어야 함
	UPROPERTY()
	TObjectPtr<class USkeletalMesh> WeaponMesh = nullptr;

	float WeaponRange = 0.0f;

	float WeaponAttackRate = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category="Skill", meta=(AllowPrivateAccess=true))
	TSubclassOf<class UGameplayAbility> SkillAbilityClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Skill", meta=(AllowPrivateAccess=true))
	TObjectPtr<class UAnimMontage> SkillActionMontage;
};
