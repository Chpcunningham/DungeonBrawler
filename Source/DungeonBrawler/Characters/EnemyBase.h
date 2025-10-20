// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONBRAWLER_API AEnemyBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	AEnemyBase();

	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveEnemy(FVector WorldDirection);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=AnimBP)
	TSubclassOf<UPaperZDAnimInstance> EnemyInstance;
};
