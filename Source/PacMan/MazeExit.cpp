// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeExit.h"
#include "GhostCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMazeExit::AMazeExit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	Box = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	Box->SetupAttachment(RootComponent);


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MazeMesh");
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMazeExit::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AMazeExit::OnOverlapBegin);
}


void AMazeExit::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	AGhostCharacter* Player = Cast<AGhostCharacter>(OtherActor);
	if (Player)
	{
		//If the player collected all the Special Item I load the final scene.
		if (Player->GetItem() == 4)
		{
			UGameplayStatics::OpenLevel(GetWorld(), "EndLevel0");
		}
	}
}
