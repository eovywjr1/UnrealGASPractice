#pragma once

#include "GameplayTagContainer.h"

#define ABTAG_ACTOR_ROTATE FGameplayTag::RequestGameplayTag(FName("Actor.Action.Rotate"))
#define ABTAG_ACTOR_ISROTATING FGameplayTag::RequestGameplayTag(FName("Actor.State.IsRotating"))
#define ABTAG_DATA_DAMAGE FGameplayTag::RequestGameplayTag(FName("Data.Damage"))
#define ABTAG_CHARCTER_ISDEAD FGameplayTag::RequestGameplayTag(FName("Character.State.IsDead"))
#define ABTAG_CHARCTER_INVINSIBLE FGameplayTag::RequestGameplayTag(FName("Character.State.Invinsible"))

#define GAMEPLAYCUE_CHARCTER_ATTACKHIT FGameplayTag::RequestGameplayTag(FName("GameplayCue.Character.AttackHit"))

#define EVENT_CHARACTER_WEAPON_EQUIP FGameplayTag::RequestGameplayTag(FName("Event.Character.Weapon.Equip"))
#define EVENT_CHARACTER_WEAPON_UNEQUIP FGameplayTag::RequestGameplayTag(FName("Event.Character.Weapon.UnEquip"))