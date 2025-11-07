// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Health/HeartBox.h"
#include "MainHud.generated.h"

/**
 * 
 */
UCLASS()
class UMainHud : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	UHeartBox* GetHeartBox() const { return HeartBox; }
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UHeartBox* HeartBox;

protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UCanvasPanel* MainCanvas;
};
