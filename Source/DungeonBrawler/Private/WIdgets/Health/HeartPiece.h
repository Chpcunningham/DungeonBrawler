// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeartPiece.generated.h"

/**
 * 
 */
UCLASS()
class UHeartPiece : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetHeartImage(bool bIsFull);
protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class USizeBox* HeartPieceWrap;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* HeartPieceImage;

	UPROPERTY(EditAnywhere, category = "HeartTextures")
	UTexture2D* FullHeartTexture;

	UPROPERTY(EditAnywhere, category = "HeartTextures")
	UTexture2D* EmptyHeartTexture;
	
	
};
