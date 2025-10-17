// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonBrawler/Characters/CharacterBase.h"
#include "DungeonHero.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class DUNGEONBRAWLER_API ADungeonHero : public ACharacterBase
{
	GENERATED_BODY()

public:
	ADungeonHero();

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
};
