// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
// #include "Engine/GameEngine.h".
#include "Engine/World.h"
#include "ReglasJuego.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlayer.h"
#include "LevelSequenceActor.h"





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
	
	ReglasJuego = Cast<AReglasJuego>(GetWorld()->GetAuthGameMode());
	
	UE_LOG(LogTemp, Display, TEXT( "Puntaje de gameMode, %f " ), ReglasJuego->superVelocidad );
	
	
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
	
}

