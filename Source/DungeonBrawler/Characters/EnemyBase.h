// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "EnemyBase.generated.h"


UCLASS()
class DUNGEONBRAWLER_API AEnemyBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	AEnemyBase();
	
	virtual void BeginPlay() override;
	
	virtual void HandleHitExtension() override;
	
	virtual void EndHitStop(ACharacterBase* ActorHitStop) override;
	
	UFUNCTION()
	void MoveEnemy(FVector WorldDirection);

	UFUNCTION()
	void OnOverlapHero(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=AnimBP)
	TSubclassOf<UPaperZDAnimInstance> EnemyInstance;

private:
	FTimerHandle EnemyHitHandle;
	float HitStopDuration = 0.1f;
};
