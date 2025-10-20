// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "AI/EnemyAI.h"
#include "PaperZDAnimationComponent.h"

AEnemyBase::AEnemyBase()
{
	AIControllerClass = AEnemyAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	GetAnimationComponent()->SetAnimInstanceClass(EnemyInstance);
}

void AEnemyBase::MoveEnemy(FVector WorldDirection)
{
	this->AddMovementInput(WorldDirection, 1.f);
}
