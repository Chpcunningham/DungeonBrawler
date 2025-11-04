// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonBrawler/Public/Components/HealthComp.h"

#include "DungeonBrawler/Characters/Hero/DungeonHero.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UHealthComp::UHealthComp()
{
	PrimaryComponentTick.bCanEverTick = true;
	MaxHealth = 3.0f;
	
}

void UHealthComp::DecreaseHealth(float Damage)
{
	CurrentHealth -= Damage;
	if (!UKismetMathLibrary::Max(CurrentHealth, 0.0f))
	{
		IsDefeated = true;
	}
}

void UHealthComp::StartInvincibility()
{
	IsInvincible = true;
	if (ADungeonHero* Hero = Cast<ADungeonHero>(GetOwner()))
	{
		Hero->GetWorldTimerManager().SetTimer(
			InvincibleHandle,
			FTimerDelegate::CreateUObject(
				this,
				&UHealthComp::EndInvincibility),
				InvincibleDuration,
				false
				);
	}
}

void UHealthComp::EndInvincibility()
{
	IsInvincible = false;
	OnInvincibilityEndDelegate.Broadcast();
}

// Called when the game starts
void UHealthComp::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}


// Called every frame
void UHealthComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
