// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleport.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


#define PRINT_ERROR(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Red,TEXT(text),false)
#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,TEXT(text),false)
#define PRINT_COMPLEX(x,...) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,FString::Printf(TEXT(x), __VA_ARGS__));}
// Sets default values
ATeleport::ATeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>("Collider");
	RootComponent = BoxCollider;

	OnActorBeginOverlap.AddDynamic(this,&ATeleport::OnOverlap);
	

}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleport::SetTeleportDirection(const FVector& Direction)
{
	TeleportDirection = Direction;
	Connection =GetActorLocation()+Direction;
	//PRINT_COMPLEX("%s",*Connection.ToString());
}

void ATeleport::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor)
		OtherActor->SetActorLocation(Connection);
}

