// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface_Grafica_userWidget.generated.h"

/**
 * 
 */
UCLASS()
class BRICKCARGAMECPP_API UInterface_Grafica_userWidget : public UUserWidget
{
	GENERATED_BODY()

	protected:
		void NativeConstruct() override;
		void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

		UPROPERTY(meta= (BindWidget) ) class UTextBlock* score;//puntaje en UI

};
