// Fill out your copyright notice in the Description page of Project Settings.

#include "PaperFlipbookComponent.h"
#include "CharacterBase.h"

ACharacterBase::ACharacterBase()
{
	GetSprite()->AddWorldRotation(FRotator(0, 0, 270.f));
}
