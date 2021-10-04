// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze.h"

#include "DrawDebugHelpers.h"
#include "Collectable.h"
#include "GhostCharacter.h"
#include "PacGhostEnemy.h"
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
// Create the Maze based on the string SEED
void AMaze::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();	
	
	const FVector MyLocation = GetActorLocation();
	if(!World) return;
	for(int i=0;i<XSize;i+=Offset)
	{
		for(int j=0;j<YSize;j+=Offset)
		{
			//ONLY DEBUG
			//DrawDebugSphere(World,FVector(i,j,0)+MyLocation,5.f, 16, FColor::Red, true) ;
			//TODO code better the index creation
			int IndexI= i/100;
			int IndexJ= j/100;
			//PRINT_COMPLEX("%d",IndexI);
			//PRINT_COMPLEX("%d",IndexI*10+IndexJ);
			int Index = LevelSeed[IndexI*10+IndexJ];
			if(Index=='1')
			{
				FVector Location = FVector(i,j,0)+MyLocation;
				SpawnStaticMeshActor(Location);
				continue;
			}
			int OffsetHalf = Offset/2;
			if(Index=='0' && PacDot)
			{
				
				FVector Location = FVector(i+OffsetHalf,j+OffsetHalf,20)+MyLocation;
				FActorSpawnParameters SpawnParameters;
				GetWorld()->SpawnActor<ACollectable>(PacDot,Location,FRotator::ZeroRotator,SpawnParameters);
				continue;
			}
			if(Index=='2' && Item)
			{
				
				FVector Location = FVector(i+OffsetHalf,j+OffsetHalf,20)+MyLocation;
				FActorSpawnParameters SpawnParameters;
				GetWorld()->SpawnActor<ACollectable>(Item,Location,FRotator::ZeroRotator,SpawnParameters);
				continue;
			}
		
			if(Index=='3' && Teleport)
			{
				//Left Teleporter
				FVector Location = FVector(i+OffsetHalf,j+OffsetHalf-Offset,20)+MyLocation;
				FActorSpawnParameters SpawnParameters;
				ATeleport* Teleporter = GetWorld()->SpawnActor<ATeleport>(Teleport,Location,FRotator::ZeroRotator,SpawnParameters);
				Teleporter->SetTeleportDirection(FVector::RightVector*YSize);
				continue;
			}
			if(Index=='4' && Teleport)
			{
				//Right Teleporter
				FVector Location = FVector(i+OffsetHalf,j+OffsetHalf+Offset,20)+MyLocation;
				FActorSpawnParameters SpawnParameters;
				ATeleport* Teleporter = GetWorld()->SpawnActor<ATeleport>(Teleport,Location,FRotator::ZeroRotator,SpawnParameters);
				Teleporter->SetTeleportDirection(FVector::LeftVector*XSize);
				continue;
			}
			if(Index=='5' && Ghost)
			{
				//GhostPlayer
				FVector Location = FVector(i+OffsetHalf,j+OffsetHalf+Offset,35)+MyLocation;
				FActorSpawnParameters SpawnParameters;
				AGhostCharacter* GhostPlayer = GetWorld()->SpawnActor<AGhostCharacter>(Ghost,Location,FRotator::ZeroRotator,SpawnParameters);
				continue;
			}
			if(Index=='6' && PacGhost)
			{
				//PacGhostEnemy
				FVector Location = FVector(i+OffsetHalf,j+OffsetHalf+Offset,0)+MyLocation;
				FActorSpawnParameters SpawnParameters;
				APacGhostEnemy* PacGhostEnemy = GetWorld()->SpawnActor<APacGhostEnemy>(PacGhost,Location,FRotator::ZeroRotator,SpawnParameters);
				
			}
			
		}
	}

	//Reset PlayerMode to GameOnly
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if(PC)
	{
		FInputModeGameOnly InputModeData;
		PC->SetInputMode(InputModeData);
	}
}

// Called every frame
void AMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Spawn Wall
void AMaze::SpawnStaticMeshActor(const FVector &InLocation) const
{
	AStaticMeshActor* MyNewActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	MyNewActor->SetMobility(EComponentMobility::Movable);
	MyNewActor->SetActorLocation(InLocation);
	MyNewActor->GetStaticMeshComponent()->SetStaticMesh(Wall);
	MyNewActor->GetStaticMeshComponent()->SetGenerateOverlapEvents(true);
	MyNewActor->SetMobility(EComponentMobility::Static);
	
	//UStaticMeshComponent* MeshComponent = MyNewActor->GetStaticMeshComponent();
	/*if (MeshComponent)
	{
		MeshComponent->SetStaticMesh(Wall);
	}*/
}





