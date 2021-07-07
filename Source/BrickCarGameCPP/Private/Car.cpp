// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
// #include "Engine/GameEngine.h".
#include "Engine/World.h"
#include "ReglasJuego.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"




// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	root = CreateDefaultSubobject<USceneComponent>(TEXT("CarRoot"));

	RootComponent = root;

	car = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("car"));

	car->AttachTo(root);

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));

	box->AttachTo(root);

	MoverSound = CreateDefaultSubobject<UAudioComponent>(TEXT("MoverSound"));

	MoverSound->AttachTo(root);

}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
	ReglasJuego = Cast<AReglasJuego>(GetWorld()->GetAuthGameMode());//obtengo el game mode

	posicionInicial = GetActorLocation();//posicion inicial

	ReglasJuego->dificultadVelocidad = velocidadInicial;//velocidad inicial
	
	currentSpeed = ReglasJuego->dificultadVelocidad;//velocidad inicial

}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("left_click_mouse", IE_Pressed, this, &ACar::ActivarSuperVelocidad );//si presiono
	PlayerInputComponent->BindAction("left_click_mouse", IE_Released, this, &ACar::DesactivarSuperVelocidad );//si suelto

}

void ACar::ActivarSuperVelocidad()
{
	if( !ReglasJuego->IfLose() && !ReglasJuego->IFGameOver() )//sino es game over y no perdiste
	{
		currentSpeed = ReglasJuego->dificultadVelocidad;//obtengo la velocidad actual
		ReglasJuego->dificultadVelocidad = ReglasJuego->superVelocidad;//super velocidad
		estoyAcelerando = true;//estoy acelerando
	}

}

void ACar::DesactivarSuperVelocidad()
{
	if( !ReglasJuego->IfLose() && !ReglasJuego->IFGameOver() ) //si el juego se esta ejecutando
	{
		ReglasJuego->dificultadVelocidad = currentSpeed;//la velocidad vuelve a la velocidad guardada antes de super velocidad
		estoyAcelerando = false;//estoy acelerando
	}
}