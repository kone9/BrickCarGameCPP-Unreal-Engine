// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover_Component.h"
#include "Engine/World.h"
#include "ReglasJuego.h"

// Sets default values for this component's properties
UMover_Component::UMover_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ReglasJuego =  Cast<AReglasJuego>(GetWorld()->GetAuthGameMode());
}


// Called every frame
void UMover_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	if( !ReglasJuego->IfLose() && !ReglasJuego->IFGameOver() )
	{
		GetOwner()->AddActorWorldOffset( FVector( 
			0,
			ReglasJuego->dificultadVelocidad * 50 * DeltaTime,
			0 
			)
		);
	}

}

