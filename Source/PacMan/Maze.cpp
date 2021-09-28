// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze.h"

#include "DrawDebugHelpers.h"
#include "Collectable.h"
#include "Engine/EngineTypes.h"
#include "Engine/StaticMeshActor.h"
#include "Teleport.h"
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
	
	const FVector MyLocation = GetActorLocation();
	if(!World) return;
	for(int i=0;i<XSize;i+=Offset)
	{
		for(int j=0;j<YSize;j+=Offset)
		{
			//DrawDebugSphere(World,FVector(i,j,0)+MyLocation,5.f, 16, FColor::Red, true) ;
			int IndexI= i/100;
			int IndexJ= j/100;
			//PRINT_COMPLEX("%d",IndexI);
			//PRINT_COMPLEX("%d",IndexI*10+IndexJ);
			int Index = LevelSeed[IndexI*10+IndexJ];
			if(Index=='1')
			{
				FVector Location = FVector(i,j,0)+MyLocation;
				SpawnStaticMeshActor(Location);
			}
			int OffsetHalf = Offset/2;
			if(Index=='0' && PacDot)
			{
				
				FVector Location = FVector(i+OffsetHalf,j+OffsetHalf,20)+MyLocation;
				FActorSpawnParameters SpawnParameters;
				GetWorld()->SpawnActor<ACollectable>(PacDot,Location,FRotator::ZeroRotator,SpawnParameters);
			}
			if(Index=='2' && PacDot)
			{
				
				FVector Location = FVector(i+OffsetHalf,j+OffsetHalf,20)+MyLocation;
				FActorSpawnParameters SpawnParameters;
				GetWorld()->SpawnActor<ACollectable>(Item,Location,FRotator::ZeroRotator,SpawnParameters);
			}
		
			if(Index=='3' && Teleport)
			{
				//Left Teleporter
				FVector Location = FVector(i+OffsetHalf,j+OffsetHalf-Offset,20)+MyLocation;
				FActorSpawnParameters SpawnParameters;
				ATeleport* Teleporter = GetWorld()->SpawnActor<ATeleport>(Teleport,Location,FRotator::ZeroRotator,SpawnParameters);
				Teleporter->SetTeleportDirection(FVector::RightVector*YSize);
			}
			if(Index=='4' && Teleport)
			{
				//Right Teleporter
				FVector Location = FVector(i+OffsetHalf,j+OffsetHalf+Offset,20)+MyLocation;
				FActorSpawnParameters SpawnParameters;
				ATeleport* Teleporter = GetWorld()->SpawnActor<ATeleport>(Teleport,Location,FRotator::ZeroRotator,SpawnParameters);
				Teleporter->SetTeleportDirection(FVector::LeftVector*XSize);
			}
			
		}
	}
}

// Called every frame
void AMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMaze::SpawnStaticMeshActor(const FVector &InLocation) const
{
	AStaticMeshActor* MyNewActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	MyNewActor->SetMobility(EComponentMobility::Movable);
	MyNewActor->SetActorLocation(InLocation);
	MyNewActor->GetStaticMeshComponent()->SetStaticMesh(Wall);
	MyNewActor->SetMobility(EComponentMobility::Static);
	
	//UStaticMeshComponent* MeshComponent = MyNewActor->GetStaticMeshComponent();
	/*if (MeshComponent)
	{
		MeshComponent->SetStaticMesh(Wall);
	}*/
}





