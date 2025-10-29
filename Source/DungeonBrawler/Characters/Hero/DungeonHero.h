// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable)
	void CheckHitBox();
	
	UFUNCTION()
	void OnAttackCompleted(bool isCompleted);

	virtual void HandleHitExtension() override;

	virtual void EndHitStop(ACharacterBase* ActorHitStop) override;

	virtual void OnStunnedOverrideCompleted(bool isCompleted) override;
	
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
private:
	bool IsAttacking;

	FTimerHandle HeroHitHandle;
	float HitStopDuration = 0.1f;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditAnywhere)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere)
	UInputAction* SwordAction;
	
	void SwingSword(const FInputActionValue& Value);
	void MoveHero(const FInputActionValue& Value);
	bool CanMoveHero();
};
