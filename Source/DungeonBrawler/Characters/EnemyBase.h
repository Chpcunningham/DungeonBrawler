// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "VFX/VFX_Base.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AVFX_Base> Skull_Explosion;
protected:
	void SetStun();
	void EndStun();
	void HandleDefeat();
	void Defeated();

	
	
private:
	FTimerHandle EnemyHitHandle;
	FTimerHandle SetStunHandle;
	FTimerHandle DespawnHandle;
	
	float HitStopDuration = 0.1f;
	float StunnedDuration = 0.5f;
	float DespawnDuration = 0.5;

	
};
