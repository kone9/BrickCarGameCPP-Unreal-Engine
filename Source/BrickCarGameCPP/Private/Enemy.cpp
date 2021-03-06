// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Engine/World.h"
#include "ReglasJuego.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Car.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"



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

	//trigger para puntaje
	BoxTriggerScore = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTriggerScore"));
	BoxTriggerScore->AttachTo(root);
	

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	ReglasJuego =  Cast<AReglasJuego>(GetWorld()->GetAuthGameMode());
	

	initialPosition = GetActorLocation();//obtengo la posición inicial
	//inicio la posición aleatoria en X
	SetActorLocation( FVector(
		CalculePositonAleatoryX(),
		GetActorLocation().Y,
		GetActorLocation().Z
		)
	);

	BoxTriggerScore->OnComponentBeginOverlap.AddDynamic(this,&AEnemy::OnComponentOverlapBeginBoxTriggerScore);//creo la dinamica


	GetWorldTimerManager().SetTimer(buscarJugador, this, &AEnemy::BuscarJugador, tiempoParaBuscarCar, false);	

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
			//reinicia posicion
			SetActorLocation( FVector (
				CalculePositonAleatoryX(),
				posicionDeReinicio + diferenciaEnReinicio.Y,//sino uso la diferencia queda desplazado
				GetActorLocation().Z
				)
			);
		}

	}
}


//calcular posicion aleatoria para usarlo en el eje X
float AEnemy::CalculePositonAleatoryX()
{
	float posicionAleatoria = FMath::RandRange(0,1);
	if(posicionAleatoria == 0)
	{
		return 500;
	}
	else
	{
		return -500;
	}
}


void AEnemy::OnComponentOverlapBeginBoxTriggerScore(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)//recibe 2 parametros que son punteros osea objetos de escena, yo y el otros
{
	if( OtherActor->GetRootComponent()->ComponentHasTag( FName("carPlayer") ) && OtherActor != this )//si tiene el root component el tag car playereste tag
	{
		UE_LOG(LogTemp, Warning, TEXT("Ganaste puntos"));
		ReglasJuego->score += 100;//sumo 100 de puntaje
	}
}

//reposiciona al auto en la posicion enicial con el X aleatorio es una Ufunction que funciona con unn delegado
void AEnemy::Reposicionar()
{
	SetActorLocation( FVector(
		CalculePositonAleatoryX(),
		initialPosition.Y,
		initialPosition.Z
		)
	);
	UE_LOG(LogTemp, Warning, TEXT("Reposicionando CarEnemy"));

}


void AEnemy::BuscarJugador()
{
	car = Cast<ACar>(UGameplayStatics::GetActorOfClass(GetWorld(), ACar::StaticClass() ));//busco el car por la clase funciona buscando la clase padre
	if(car == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No existe esa clase en el juego"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Existe esa clase CAR"));
		// car->ReposicionarEnemigoAlMorirEvento.BindUObject(this,&AEnemy::Reposicionar);//ya tengo el evento activado
		car->ReposicionarEnemigoAlMorirEvento.AddUObject(this, &AEnemy::Reposicionar);
	}

}