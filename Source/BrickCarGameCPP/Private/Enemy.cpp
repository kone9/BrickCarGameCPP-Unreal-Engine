// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Engine/World.h"
#include "ReglasJuego.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	carEnemy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("carEnemy"));
	carEnemy->AttachTo(root);


	boxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("boxTrigger"));
	boxTrigger->AttachTo(root);

	BoxTriggerScore = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTriggerScore"));
	BoxTriggerScore->AttachTo(root);
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	ReglasJuego =  Cast<AReglasJuego>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if( !ReglasJuego->IfLose() && !ReglasJuego->IFGameOver() )//sino es lose y no es game over
	{

		if(GetActorLocation().Y > cuandoLlegaHasta)//cuando llega hasta esta posición
		{
			
			diferenciaEnReinicio.Y = GetActorLocation().Y - cuandoLlegaHasta;//diferencia de reinicio para evitar el desplazamiento

			SetActorLocation( FVector (
				GetActorLocation().X,
				posicionDeReinicio + diferenciaEnReinicio.Y,//sino uso la diferencia queda desplazado
				GetActorLocation().Z
				)
			);
		}

	}


}

