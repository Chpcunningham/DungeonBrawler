// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "AI/EnemyAI.h"
#include "PaperZDAnimationComponent.h"
#include "Components/BoxComponent.h"
#include "Components/HealthComp.h"
#include "Hero/DungeonHero.h"
#include "Kismet/GameplayStatics.h"

AEnemyBase::AEnemyBase()
{
	AIControllerClass = AEnemyAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HurtBox->SetBoxExtent(FVector(22.f, 22.f, 70.f));
	HurtBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlapHero);

	this->SetCanBeDamaged(true);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	GetAnimationComponent()->SetAnimInstanceClass(EnemyInstance);
}

void AEnemyBase::MoveEnemy(FVector WorldDirection)
{
	if (!this->HealthComp->IsDefeated)
	{
		this->AddMovementInput(WorldDirection, 1.f);
	}
}

void AEnemyBase::OnOverlapHero(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult& SweepResult)
{
	if (!HealthComp->IsDefeated)
	{
		if (ADungeonHero* Hero = Cast<ADungeonHero>(OtherActor))
		{
			if (Hero->HurtBox == OtherComp)
			{
				UGameplayStatics::ApplyDamage(Hero, 1.f, this->GetController(), this, UDamageType::StaticClass());
			}
		}
	}
}
