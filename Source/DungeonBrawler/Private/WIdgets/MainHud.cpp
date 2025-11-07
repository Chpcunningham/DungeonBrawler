// Fill out your copyright notice in the Description page of Project Settings.


#include "WIdgets/MainHud.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"

void UMainHud::NativeConstruct()
{
	Super::NativeConstruct();
	WidgetTree->RootWidget = MainCanvas;
}
