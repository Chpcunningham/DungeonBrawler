// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONBRAWLER_API UHealthComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComp();

	UFUNCTION()
	void DecreaseHealth(float Damage);

	UPROPERTY(EditAnywhere, Category=Health)
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category=Health)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category=Health)
	bool IsDefeated = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
