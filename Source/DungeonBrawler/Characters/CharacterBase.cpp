// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "PaperZDAnimInstance.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Components/BoxComponent.h"
#include "DungeonBrawler/Public/Components/HealthComp.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


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

	KnockbackTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("KnockbackTimeline"));
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (KnockbackTimeline)
	{
		KnockbackCurve = NewObject<UCurveFloat>(this, TEXT("KnockbackCurve"));
		if (KnockbackCurve)
		{
			KnockbackCurve->FloatCurve.AddKey(0.0f, 1.0f);
			KnockbackCurve->FloatCurve.AddKey(1.0f, 0.0f);

			KnockbackUpdate.BindUFunction(this, FName("KnockbackTimelineUpdate"));
			KnockbackTimeline->AddInterpFloat(KnockbackCurve, KnockbackUpdate);
			KnockbackTimeline->SetTimelineLength(1.f);
		}
	}
}

void ACharacterBase::AnyDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
                                    class AController* InstigatedBy, AActor* DamageCauser)
{
	if (!HealthComp->IsDefeated)
	{
		HealthComp->DecreaseHealth(Damage);
		GetKnockBack(DamageCauser);

		GetSprite()->SetSpriteColor(FColor::Red);
		GetWorldTimerManager().SetTimer(
			FlashSpriteHandle,
			this,
			&ACharacterBase::SpriteBackToWhite,
			0.2f,
			false
		);


		if (ACharacterBase* HitActor = Cast<ACharacterBase>(DamagedActor))
		{
			if (ACharacterBase* ActorHitStop = Cast<ACharacterBase>(DamageCauser))
			{
				//HitActor->CustomTimeDilation = 0.f;
				ActorHitStop->CustomTimeDilation = 0.f;
				GetWorldTimerManager().SetTimer(
					HitStopHandle,
					FTimerDelegate::CreateUObject(
						this, &ACharacterBase::EndHitStop, ActorHitStop
					),
					HitStopDuration,
					false

				);
				HitActor->HandleHitExtension();
			}
		}
		// if (UPaperZDAnimInstance* CharAnimInstance = GetAnimationComponent()->GetAnimInstance())
		// {
		// 	IsStunned = true;
		// 	CharAnimInstance->PlayAnimationOverride(
		// 		StunnedSequence,
		// 		FName("DefaultSlot"),
		// 		1.f,
		// 		0,
		// 		FZDOnAnimationOverrideEndSignature::CreateUObject(this, &ACharacterBase::OnStunnedOverrideCompleted));
		// }
	}
}

void ACharacterBase::GetKnockBack(AActor* Actor)
{
	FVector DamageCauser = Actor->GetActorLocation();
	FVector DamagedActor = this->GetActorLocation();

	FRotator Direction = UKismetMathLibrary::FindLookAtRotation(DamageCauser, DamagedActor);

	KnockbackVector = UKismetMathLibrary::GetForwardVector(Direction);

	KnockbackTimeline->SetPlayRate(5.f);
	KnockbackTimeline->PlayFromStart();
}

void ACharacterBase::SpriteBackToWhite()
{
	GetSprite()->SetSpriteColor(FColor::White);
}

void ACharacterBase::EndHitStop(ACharacterBase* ActorHitStop)
{
	ActorHitStop->CustomTimeDilation = 1.f;
}


void ACharacterBase::KnockbackTimelineUpdate(float Value)
{
	FVector TotalKnockback = UKismetMathLibrary::Multiply_VectorFloat(KnockbackVector, KnockbackStrength);
	this->GetCharacterMovement()->Velocity = TotalKnockback;
}

void ACharacterBase::OnStunnedOverrideCompleted(bool isCompleted)
{
	IsStunned = false;

	if (this->HealthComp->IsDefeated)
	{
		if (UPaperZDAnimInstance* CharAnimInstance = GetAnimationComponent()->GetAnimInstance())
		{
			CharAnimInstance->JumpToNode(FName("DeadJump"));
		}
	}
}
