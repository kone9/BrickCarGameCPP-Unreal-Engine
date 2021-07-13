// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
// #include "Engine/GameEngine.h".
#include "Engine/World.h"
#include "ReglasJuego.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Enemy.h"

// #define AddDynamic(UserObject,FuncName) __Internal_AddDynamic( UserObject, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) ) )

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	root = CreateDefaultSubobject<USceneComponent>(TEXT("CarRoot"));
	RootComponent = root;

	car = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("car"));
	car->AttachTo(root);

	//para trigger
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	box->AttachTo(root);
	
	// box->SetGenerateOverlapEvents(true);
	// box->SetCollisionResponseToAllChannels(ECR_Overlap);
	// box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//activamos la dinamica
	// box->SetCollisionProfileName("Car");//agregamos a la mascara de colision
	// box->OnComponentBeginOverlap.AddDynamic(this, &ACar::OnTriggerEnter);//creo la dinamica para el trigger en el root
	
	//para sonidos
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

	box->OnComponentBeginOverlap.AddDynamic(this, &ACar::OnOverlapBegin);
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
	PlayerInputComponent->BindAction("Mover_derecha",IE_Pressed,this,&ACar::MoverDerecha);
	PlayerInputComponent->BindAction("Mover_izquierda",IE_Pressed,this,&ACar::MoverIzquierda);
}

//super velocidad
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


//mover derecha
void ACar::MoverDerecha()
{
	if(!ReglasJuego->IfLose())//sino es game over
	{
		if(GetActorLocation().X < 500)
		{
			float moverDerecha = GetActorLocation().X + 1000;

			FVector posicionNueva = FVector( 
				moverDerecha,
				GetActorLocation().Y,
				GetActorLocation().Z 
			);
			
			SetActorLocation( posicionNueva );

			//activo sonido mover
		}
	}
}

//mover izquierda
void ACar::MoverIzquierda()
{
	if(!ReglasJuego->IfLose())//sino es game over
	{
		if(GetActorLocation().X > -500)
		{
			float moverDerecha = GetActorLocation().X - 1000;//se resta a la posicion actual

			FVector posicionNueva = FVector( 
				moverDerecha,
				GetActorLocation().Y,
				GetActorLocation().Z 
			);
			
			SetActorLocation( posicionNueva );

			//activo sonido mover
		}
	}
}

//cuando algo entra activo eventos
void ACar::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)//recibe 2 parametros que son punteros osea objetos de escena, yo y el otros
{
	if(OtherComp->ComponentHasTag("carEnemy") && OtherActor != this)//si el componente tiene el tag CarEnemy y es distinto de este mismo
	{
		ReglasJuego->vidas -=1;//descuento una vida
		UE_LOG(LogTemp, Warning, TEXT("Chocaste contra el enemigo"));
		ReglasJuego->lose = true;
		SetActorLocation(posicionInicial);//vuelvo a la posición inicial
	}
}