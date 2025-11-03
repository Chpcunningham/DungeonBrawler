// Fill out your copyright notice in the Description page of Project Settings.


#include "VFX/VFX_Base.h"

#include "PaperFlipbookComponent.h"

// Sets default values
AVFX_Base::AVFX_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Effect = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Effect"));
	Effect->SetupAttachment(GetRootComponent());
	Effect->SetWorldRotation(FRotator(0, 0, 270.f));

	Effect->OnFinishedPlaying.AddDynamic(this, &AVFX_Base::EndEffect);

	Effect->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AVFX_Base::BeginPlay()
{
	Super::BeginPlay();

	Effect->SetLooping(false);
}

// Called every frame
void AVFX_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVFX_Base::EndEffect()
{
	this->Destroy();
}

