// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze.h"

#include "DrawDebugHelpers.h"

#define PRINT_ERROR(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Red,TEXT(text),false)
#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,TEXT(text),false)
#define PRINT_COMPLEX(x,...) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,FString::Printf(TEXT(x), __VA_ARGS__));}
// Sets default values
AMaze::AMaze()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMaze::BeginPlay()
{
	Super::BeginPlay();
	/*DrawDebugSphere(GetWorld(), StartLocation, 10.f, 32, FColor::Red, false, 5.f);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 4.9f, 0, 1.f);*/
	UWorld* World = GetWorld();
	if(!World) return;
	for(int i=0;i<XSize;i+=Offset)
	{
		for(int j=0;j<YSize;j+=Offset)
		{
			DrawDebugSphere(GetWorld(),FVector(i,j,0)+GetActorLocation(),10.f, 32, FColor::Red, false, 5.f);
		}
	}
}

// Called every frame
void AMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

