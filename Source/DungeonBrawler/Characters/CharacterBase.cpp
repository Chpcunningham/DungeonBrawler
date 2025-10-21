// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "DungeonBrawler/Public/Components/HealthComp.h"
#include "GameFramework/CharacterMovementComponent.h"


ACharacterBase::ACharacterBase()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 3600.0f, 0.f);
	
	GetSprite()->AddWorldRotation(FRotator(0, 0, 270.f));
	GetSprite()->SetUsingAbsoluteRotation(true);

	HurtBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HurtBox"));
	HurtBox->SetupAttachment(RootComponent);

	OnTakeAnyDamage.AddDynamic(this, &ACharacterBase::AnyDamageTaken);
	HealthComp = CreateDefaultSubobject<UHealthComp>(TEXT("HealthComp"));
	
	this->SetCanBeDamaged(true);
	
}

void ACharacterBase::AnyDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (!HealthComp->IsDefeated)
	{
		HealthComp->DecreaseHealth(Damage);
		GEngine->AddOnScreenDebugMessage(0, 4.5f, FColor::Blue, FString::Printf(TEXT("Defeated: %s"), HealthComp->IsDefeated ? TEXT("true") : TEXT("false")));
	}
	
}
