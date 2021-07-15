// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"



UCLASS()
class BRICKCARGAMECPP_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	//componentes principales
	UPROPERTY(VisibleAnywhere) USceneComponent * root; //root de todo el blueprint

	UPROPERTY(VisibleAnywhere) class UStaticMeshComponent* carEnemy;//auto

	UPROPERTY(VisibleAnywhere) class UBoxComponent* boxTrigger;//caja de colision

	UPROPERTY(VisibleAnywhere) class UBoxComponent* BoxTriggerScore;//caja de colision


protected:
	UPROPERTY(EditAnywhere)
	float velocidad = -1000;

	UPROPERTY(EditAnywhere)
	float cuandoLlegaHasta = 3000;

	UPROPERTY(EditAnywhere)
	float posicionDeReinicio = -7000;

	UFUNCTION()
	void OnComponentOverlapBeginBoxTriggerScore(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);//recibe 2 parametros que son punteros osea objetos de escena, yo y el otros
	
	class ACar* car;//referencia al car de la esncea

private:
	class AReglasJuego* ReglasJuego;//puntero al game mode principal0.
	
	FVector initialPosition;//posicion de reinicio
	
	FVector diferenciaEnReinicio;

	float CalculePositonAleatoryX();//calcular posicion aleatoria en X

private:
	//buscar jugador y uso del delegado
	FTimerHandle buscarJugador;

	UPROPERTY(EditAnywhere) float tiempoParaBuscarCar = 0.2f;

	void BuscarJugador();

	UFUNCTION()//para usar con delegado importante que sea UFUNCTION
	void Reposicionar();//para usar con el delegado importantisimo que sea una UFUNCTIONs
};
