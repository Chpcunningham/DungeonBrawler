// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "AnimSequences/PaperZDAnimSequence.h"
#include "Components/TimelineComponent.h"
#include "CharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONBRAWLER_API ACharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	bool IsStunned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* HurtBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Component")
	class UHealthComp* HealthComp;

	UFUNCTION()
	void GetKnockBack(AActor* Actor);

	UFUNCTION()
	void KnockbackTimelineUpdate(float Value);
	
	UFUNCTION()
	void OnStunnedOverrideCompleted(bool isCompleted);
	
	UFUNCTION()
	void AnyDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

protected:
	UPROPERTY(EditAnywhere)
	UTimelineComponent* KnockbackTimeline;

	UPROPERTY(EditAnywhere, Category=AnimSequences)
	class UPaperZDAnimSequence* StunnedSequence;

	UPROPERTY(EditAnywhere, Category=AnimSequences)
	class UPaperZDAnimSequence* SwordAttackSequence;
	
	UPROPERTY(EditAnywhere)
	float KnockbackStrength = 1000.f;

	UPROPERTY(EditAnywhere)
	FVector KnockbackVector;

	UPROPERTY(EditAnywhere)
	class UCurveFloat* KnockbackCurve;
	
private:
	FOnTimelineFloat KnockbackUpdate; 
};
