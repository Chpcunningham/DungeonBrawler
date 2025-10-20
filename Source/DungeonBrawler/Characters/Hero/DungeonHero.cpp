// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonHero.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "PaperZDAnimationComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
	HitBox->SetWorldLocation(FVector(30.f,0.f,0.f));
}

void ADungeonHero::BeginPlay()
{
	Super::BeginPlay();

	GetAnimationComponent()->SetAnimInstanceClass(HeroInstance);
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem  = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			PlayerSubsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ADungeonHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADungeonHero::MoveHero);
	}
}

void ADungeonHero::MoveHero(const FInputActionValue& Value)
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
