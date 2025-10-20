// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAI.h"
#include "DungeonBrawler/Characters/EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void AEnemyAI::OnPossess(class APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedPawn = Cast<AEnemyBase>(InPawn);
}

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	TargetHero = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TargetHero)
	{
		FVector ForwardVectorTarget;
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(
			PossessedPawn->GetActorLocation(), TargetHero->GetActorLocation());

		ForwardVectorTarget = UKismetMathLibrary::GetForwardVector(TargetRotation);

		PossessedPawn->MoveEnemy(ForwardVectorTarget);
	}
}
