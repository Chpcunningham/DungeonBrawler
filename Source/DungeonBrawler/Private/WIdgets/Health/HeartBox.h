// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeartPiece.h"
#include "Blueprint/UserWidget.h"
#include "HeartBox.generated.h"

/**
 * 
 */
UCLASS()
class UHeartBox : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void InitializeHealth(TSubclassOf<UHeartPiece> HeartPiece, float Maxhealth) const;

	UFUNCTION()
	void UpdateCurrentHealth(float CurrentHealth) const;

protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UHorizontalBox* HeartBoxWidget;
	
};
