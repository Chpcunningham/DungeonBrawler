// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "PaperFlipbookComponent.h"


ACharacterBase::ACharacterBase()
{
	GetSprite()->AddWorldRotation(FRotator(0, 0, 270.f));
}
