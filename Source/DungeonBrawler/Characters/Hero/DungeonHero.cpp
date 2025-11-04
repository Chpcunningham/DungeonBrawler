// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonHero.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "PaperZDAnimationComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"
#include "Components/BoxComponent.h"
#include "Components/HealthComp.h"
#include "DungeonBrawler/Characters/EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ADungeonHero::ADungeonHero()
{
	//Set up rotation for hit boxes
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	GetSprite()->SetUsingAbsoluteRotation(true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetWorldRotation(FRotator(270.f, 270.f, 0));
	SpringArm->SetUsingAbsoluteRotation(true);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraComponent->SetupAttachment(SpringArm);
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->OrthoWidth = 800.f;

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(GetCapsuleComponent());
	HitBox->SetWorldLocation(FVector(30.f, 0.f, 0.f));

	HurtBox->SetBoxExtent(FVector(22.f, 22.f, 70.f));
}

void ADungeonHero::BeginPlay()
{
	Super::BeginPlay();

	GetAnimationComponent()->SetAnimInstanceClass(HeroInstance);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			PlayerSubsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	HealthComp->OnInvincibilityEndDelegate.AddDynamic(this, &ADungeonHero::OnInvincibilityEnd_DelegateSignature);
}

void ADungeonHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADungeonHero::MoveHero);
		EnhancedInput->BindAction(SwordAction, ETriggerEvent::Started, this, &ADungeonHero::SwingSword);
	}
}

void ADungeonHero::SwingSword(const FInputActionValue& Value)
{
	if (CanMoveHero())
	{
		if (UPaperZDAnimInstance* CharAnimInstance = GetAnimationComponent()->GetAnimInstance())
		{
			IsAttacking = true;

			CharAnimInstance->PlayAnimationOverride(
				SwordAttackSequence,
				FName("DefaultSlot"),
				2.f,
				0,
				FZDOnAnimationOverrideEndSignature::CreateUObject(this, &ADungeonHero::OnAttackCompleted));
		}
	}
}

void ADungeonHero::OnAttackCompleted(bool isCompleted)
{
	IsAttacking = false;
}

void ADungeonHero::FlashSpriteVisibility()
{
	if (GetSprite())
	{
		GetSprite()->SetVisibility(!GetSprite()->IsVisible());
	}
}

void ADungeonHero::HandleSpriteVisibility()
{
	if (!IsValid(this)) return;
	
	GetWorldTimerManager().SetTimer(
			VisibleHandle,
			FTimerDelegate::CreateUObject(
				this,
				&ADungeonHero::FlashSpriteVisibility
				),
				0.1f,
				true
				);
}

void ADungeonHero::HandleHitExtension()
{
	HealthComp->StartInvincibility();
	if (UPaperZDAnimInstance* CharAnimInstance = GetAnimationComponent()->GetAnimInstance())
	{
		IsStunned = true;

		if (ACharacterBase* Hero = Cast<ACharacterBase>(this))
		{
			Hero->CustomTimeDilation = 0.f;
			GetWorldTimerManager().SetTimer(
				HeroHitHandle,
				FTimerDelegate::CreateUObject(
					this, &ADungeonHero::EndHitStop, Hero
				),
				this->HitStopDuration,
				false
			);
		}

		CharAnimInstance->PlayAnimationOverride(
			StunnedSequence,
			FName("DefaultSlot"),
			1.f,
			0,
			FZDOnAnimationOverrideEndSignature::CreateUObject(this, &ADungeonHero::OnStunnedOverrideCompleted));
	}
}

void ADungeonHero::EndHitStop(ACharacterBase* ActorHitStop)
{
	Super::EndHitStop(ActorHitStop);
}

void ADungeonHero::OnStunnedOverrideCompleted(bool isCompleted)
{
	Super::OnStunnedOverrideCompleted(isCompleted);
}

void ADungeonHero::MoveHero(const FInputActionValue& Value)
{
	if (CanMoveHero())
	{
		FVector2D MovementVector = Value.Get<FVector2D>();

		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightVector = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardVector, MovementVector.X);
		AddMovementInput(RightVector, MovementVector.Y);

		Directionality = FVector2D(MovementVector.X, MovementVector.Y);
	}
}

bool ADungeonHero::CanMoveHero()
{
	if (!IsStunned && !HealthComp->IsDefeated && !IsAttacking)
	{
		return true;
	}
	return false;
}

void ADungeonHero::OnInvincibilityEnd_DelegateSignature()
{
	GetWorldTimerManager().ClearTimer(VisibleHandle);
	GetSprite()->SetVisibility(true);
}

void ADungeonHero::CheckHitBox()
{
	TArray<AActor*> OverlappingActors;
	HitBox->GetOverlappingActors(OverlappingActors, AEnemyBase::StaticClass());

	for (auto It = OverlappingActors.rbegin(); It != OverlappingActors.rend(); ++It)
	{
		UGameplayStatics::ApplyDamage(*It, 1.f, GetController(), this, UDamageType::StaticClass());
	}
}
