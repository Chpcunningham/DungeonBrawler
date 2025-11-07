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

void UHeartBox::InitializeHealth(UHeartPiece* HeartPiece)
{
	this->HeartBoxWidget->AddChild(HeartPiece);
}
