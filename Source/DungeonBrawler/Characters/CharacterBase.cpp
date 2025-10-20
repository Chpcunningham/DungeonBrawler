// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ACharacterBase::ACharacterBase()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 3600.0f, 0.f);
	
	GetSprite()->AddWorldRotation(FRotator(0, 0, 270.f));
	GetSprite()->SetUsingAbsoluteRotation(true);
}
