// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonBrawler/Characters/CharacterBase.h"
#include "DungeonHero.generated.h"

class UCameraComponent;
class UBoxComponent;
class UInputAction;
struct FInputActionValue;
class UInputMappingContext;
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

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	void MoveHero(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Directionality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPaperZDAnimInstance> HeroInstance;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditAnywhere)
	UInputAction* MoveAction; 
};
