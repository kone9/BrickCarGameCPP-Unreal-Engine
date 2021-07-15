// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Car.generated.h"


// DECLARE_DELEGATE(EventoMurioJugador)
DECLARE_MULTICAST_DELEGATE(EventoMurioJugador)//es un multicast se usa e muchos lados
UCLASS()
class BRICKCARGAMECPP_API ACar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar();

	//delegados eventos dispacher
	EventoMurioJugador ReposicionarEnemigoAlMorirEvento;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//componentes principales
	UPROPERTY(VisibleAnywhere)
	USceneComponent * root; //root de todo el blueprint

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* car;//auto

	UPROPERTY(EditAnywhere)
	class UBoxComponent* box;//caja de colision

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* MoverSound;//sonido
	
protected:
	class AReglasJuego* ReglasJuego;//puntero al game mode principal0.

	
private:
	FVector posicionInicial;

	UPROPERTY(EditAnywhere)
	float velocidadInicial = 50;

	UPROPERTY(EditAnywhere)
	float currentSpeed = 0;

	bool estoyAcelerando = false;

private:
	void ActivarSuperVelocidad();
	void DesactivarSuperVelocidad();
	void MoverDerecha();
	void MoverIzquierda();

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
