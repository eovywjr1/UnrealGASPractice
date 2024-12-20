// Fill out your copyright notice in the Description page of Project Settings.


#include "GC/ABGC_AttackHit.h"

#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

UABGC_AttackHit::UABGC_AttackHit()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionRef(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (ExplosionRef.Object)
	{
		ParticleSystem = ExplosionRef.Object;
	}
}

bool UABGC_AttackHit::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	if (const FHitResult* HitResult = Parameters.EffectContext.GetHitResult())
	{
		UGameplayStatics::SpawnEmitterAtLocation(MyTarget, ParticleSystem, HitResult->ImpactPoint, FRotator::ZeroRotator, true);
	}
	else
	{
		for (const TWeakObjectPtr<AActor>& TargetActor : Parameters.EffectContext.Get()->GetActors())
		{
			if (TargetActor.Get())
			{
				UGameplayStatics::SpawnEmitterAtLocation(MyTarget, ParticleSystem, TargetActor->GetActorLocation(), FRotator::ZeroRotator, true);
			}
		}
	}

	return false;
}
