// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleport.h"
#include "Components/BoxComponent.h"

//Class representing the teleporting block

// Sets default values
ATeleport::ATeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>("Collider");
	RootComponent = BoxCollider;

	
	

}
//Set when the object is spawned in Maze.cpp
//@param Offset (already scaled on the maze size) that represents where the
//actor should appear when entering the teleport block.
void ATeleport::SetTeleportDirection(const FVector& Offset)
{
	Connection =GetActorLocation()+Offset;
}

void ATeleport::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor)
		OtherActor->SetActorLocation(Connection);
}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this,&ATeleport::OnOverlap);
}

