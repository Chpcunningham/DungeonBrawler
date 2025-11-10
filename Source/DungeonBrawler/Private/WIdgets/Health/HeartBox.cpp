// Fill out your copyright notice in the Description page of Project Settings.


#include "WIdgets/Health/HeartBox.h"

#include "HeartPiece.h"
#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"
#include "Components/HorizontalBox.h"

void UHeartBox::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHeartBox::InitializeHealth(TSubclassOf<UHeartPiece> HeartPiece, float Maxhealth) const
{
	if (!HeartPiece) return;
	if (Maxhealth <= 0) return;
	
	for (int i = 0; i < Maxhealth; i++)
	{
		//Create a new instance of the heart instead of reusing the same one
		UHeartPiece* NewPiece = CreateWidget<UHeartPiece>(GetWorld(), HeartPiece);

		//Add that new piece
		HeartBoxWidget->AddChild(NewPiece);
	}
}

void UHeartBox::UpdateCurrentHealth(float CurrentHealth) const
{
	int32 index = 0;
	for (UWidget* Heart : HeartBoxWidget->GetAllChildren())
	{
		bool bSetHeart = index < CurrentHealth;
		if (UHeartPiece* HeartPiece = Cast<UHeartPiece>(Heart))
		{
			HeartPiece->SetHeartImage(bSetHeart);
		}
		index++;
	}
}
