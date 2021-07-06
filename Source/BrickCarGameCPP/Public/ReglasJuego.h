// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ReglasJuego.generated.h"

/**
 * 
 */
UCLASS()
class BRICKCARGAMECPP_API AReglasJuego : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
		UPROPERTY(EditAnywhere) int vidas;
		UPROPERTY(EditAnywhere) int score;
		UPROPERTY(EditAnywhere) int goal;
		UPROPERTY(EditAnywhere) int higtScore;
		UPROPERTY(EditAnywhere) int puntosParaGanar;
		UPROPERTY(EditAnywhere) bool lose;
		UPROPERTY(EditAnywhere) bool gameOver;
		UPROPERTY(EditAnywhere) float dificultadVelocidad;
		UPROPERTY(EditAnywhere) float superVelocidad;

		bool IfLose();
		bool IFGameOver();


};
