// Fill out your copyright notice in the Description page of Project Settings.


#include "WIdgets/Health/HeartPiece.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"

void UHeartPiece::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHeartPiece::SetHeartImage(bool bIsFull)
{
	if (bIsFull)
	{
		HeartPieceImage->SetBrushFromTexture(FullHeartTexture);
	}
	else if (!bIsFull)
	{
		HeartPieceImage->SetBrushFromTexture(EmptyHeartTexture);
	}
}
