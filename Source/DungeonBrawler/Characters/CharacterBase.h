// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Component")
	class UHealthComp* HealthComp;

	UFUNCTION()
	void AnyDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* HurtBox;
};
