// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeExit.h"

#include "GhostCharacter.h"


#define PRINT_ERROR(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Red,TEXT(text),false)
#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,TEXT(text),false)
#define PRINT_COMPLEX(x,...) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,FString::Printf(TEXT(x), __VA_ARGS__));}
// Sets default values
AMazeExit::AMazeExit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MazeMesh");
	Mesh->SetupAttachment(Root);

	OnActorBeginOverlap.AddDynamic(this,&AMazeExit::OnOverlap);

}

// Called when the game starts or when spawned
void AMazeExit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeExit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeExit::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!OtherActor) return;
	if(OtherActor->IsA(AGhostCharacter::StaticClass()))
	{
		if(!Player)
		{
			Player = Cast<AGhostCharacter>(OtherActor);
		}

	if(Player->GetItem()==4)
	{
		PRINT("YOU WON");
	}
	}
}

