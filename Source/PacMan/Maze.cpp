// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze.h"

#include "DrawDebugHelpers.h"
#include "Collectable.h"
#include "GhostCharacter.h"
#include "MazeExit.h"
#include "PacGhostEnemy.h"
#include "Engine/EngineTypes.h"
#include "Engine/StaticMeshActor.h"
#include "Teleport.h"
#include "SoundManager.h"

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
	if (!World) return;
	bool IsExitCreated = false;
	const FVector MyLocation = GetActorLocation();

	for (int i = 0; i < XSize; i += Offset)
	{
		for (int j = 0; j < YSize; j += Offset)
		{
			//ONLY DEBUG
			//DrawDebugSphere(World,FVector(i,j,0)+MyLocation,5.f, 16, FColor::Red, true) ;
			int IndexI = i / Offset;
			int IndexJ = j / Offset;
			int SeedDigit = LevelSeed[IndexI * ScaleFactor + IndexJ];

			//Simple Wall (pivot in the corner)
			if (SeedDigit == '1')
			{
				FVector Location = FVector(i, j, 0) + MyLocation;
				SpawnStaticMeshActor(Location);
				continue;
			}

			int OffsetHalf = Offset / 2;
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			//Yellow Dot (Pivot in the center)
			if (SeedDigit == '0' && PacDot)
			{
				FVector Location = FVector(i + OffsetHalf, j + OffsetHalf, 20) + MyLocation;

				GetWorld()->SpawnActor<ACollectable>(PacDot, Location, FRotator::ZeroRotator, SpawnParameters);
				continue;
			}
			//Special Item (Pivot in the center)
			if (SeedDigit == '2' && Item)
			{
				FVector Location = FVector(i + OffsetHalf, j + OffsetHalf, 20) + MyLocation;
				GetWorld()->SpawnActor<ACollectable>(Item, Location, FRotator::ZeroRotator, SpawnParameters);
				continue;
			}

			//Left Teleporter (pivot in the center) 
			if (SeedDigit == '3' && Teleport)
			{
				//The teleport is located outside the row of wall
				FVector Location = FVector(i + OffsetHalf, j + OffsetHalf - Offset, 20) + MyLocation;
				ATeleport* Teleporter = GetWorld()->SpawnActor<ATeleport>(
					Teleport, Location, FRotator::ZeroRotator, SpawnParameters);
				Teleporter->SetTeleportDirection(FVector::RightVector * YSize);
				continue;
			}
			//Right Teleporter (pivot in the center)
			if (SeedDigit == '4' && Teleport)
			{
				//The teleport is located outside the row of wall
				FVector Location = FVector(i + OffsetHalf, j + OffsetHalf + Offset, 20) + MyLocation;
				ATeleport* Teleporter = GetWorld()->SpawnActor<ATeleport>(
					Teleport, Location, FRotator::ZeroRotator, SpawnParameters);
				Teleporter->SetTeleportDirection(FVector::LeftVector * XSize);
				continue;
			}
			//Player character (pivot center)
			if (SeedDigit == '5' && Ghost)
			{
				//GhostPlayer
				FVector Location = FVector(i + OffsetHalf, j + OffsetHalf + Offset, 35) + MyLocation;

				Player = GetWorld()->SpawnActor<AGhostCharacter>(Ghost, Location, FRotator::ZeroRotator,
				                                                 SpawnParameters);
				PlayerSpawn = Location;
				Player->OnEat.AddDynamic(this, &AMaze::ResetNotification);
				continue;
			}
			//Enemies character (pivot center)
			if (SeedDigit == '6' && PacGhost)
			{
				//PacGhostEnemy
				FVector Location = FVector(i + OffsetHalf, j + OffsetHalf + Offset, 0) + MyLocation;
				//Ghost are spawned one by one after the maze initilization
				EnemiesSpawn.Add(Location);
				continue;
			}
			//Maze Exit (Pivot corner)
			if (SeedDigit == '7' && !IsExitCreated && MazeExit)
			{
				IsExitCreated = true;
				FVector Location = FVector(i, j, 0) + MyLocation;

				AMazeExit* Exit = GetWorld()->SpawnActor<AMazeExit>(MazeExit, Location, FRotator::ZeroRotator,
				                                                    SpawnParameters);
			}
		}
	}


	//Reset PlayerMode to GameOnly
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		FInputModeGameOnly InputModeData;
		PC->SetInputMode(InputModeData);
	}

	//SpawnAudioManager
	FActorSpawnParameters SpawnParameters;
	Audio = GetWorld()->SpawnActor<ASoundManager>(AudioManager, FVector(0, 0, -100), FRotator::ZeroRotator,
	                                              SpawnParameters);
	//SpawnEnemies
	SpawnCounter = EnemiesSpawn.Num();
	GetWorldTimerManager().SetTimer(EnemySpawnHandle, this, &AMaze::SpawnPacManGhost, 1.f, true, 1.f);
}


//Spawn Wall
void AMaze::SpawnStaticMeshActor(const FVector& InLocation) const
{
	AStaticMeshActor* MyNewActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	MyNewActor->SetMobility(EComponentMobility::Movable);
	MyNewActor->SetActorLocation(InLocation);
	MyNewActor->GetStaticMeshComponent()->SetStaticMesh(Wall);
	MyNewActor->GetStaticMeshComponent()->SetGenerateOverlapEvents(true);
	MyNewActor->SetMobility(EComponentMobility::Static);
}

//When the player is eaten reset all actors in their starting position
//if the play has no life the game end.
void AMaze::ResetNotification(int Value)
{
	if (Value > 0)
	{
		Player->SetActorEnableCollision(false);
		
		for (int i = 0; i < Enemies.Num(); i++)
		{
			Enemies[i]->SetActorHiddenInGame(true);
			Enemies[i]->SetActorEnableCollision(false);
		}
		GetWorldTimerManager().SetTimer(ResetHandle, this, &AMaze::ResetPosition, 1.2f, false);
	}
	else
	{
		for (auto& X : Enemies)
		{
			X->Destroy();
		}
		Enemies.Empty();
		Player->Destroy();
	}
}

void AMaze::ResetPosition()
{
	
	
	Player->SetActorLocation(PlayerSpawn);
	Player->SetActorEnableCollision(true);
	for (int i = 0; i < Enemies.Num(); i++)
	{
		Enemies[i]->SetActorHiddenInGame(false);
		Enemies[i]->SetActorEnableCollision(true);
		Enemies[i]->SetActorLocation(EnemiesSpawn[i]);
	}
}

void AMaze::ResetEnemyKilled(AActor* Enemy)
{
	if (Enemy)
	{
		APacGhostEnemy* X = Cast<APacGhostEnemy>(Enemy);
		int Index = Enemies.Find(X);
		X->SetActorLocation(EnemiesSpawn[Index]);
	}
}

void AMaze::SpawnPacManGhost()
{
	if (SpawnCounter == 0)
	{
		GetWorldTimerManager().ClearTimer(EnemySpawnHandle);
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	APacGhostEnemy* PacGhostEnemy = GetWorld()->SpawnActor<APacGhostEnemy>(
		PacGhost, EnemiesSpawn[SpawnCounter - 1], FRotator::ZeroRotator, SpawnParameters);
	if (PacGhostEnemy)
	{
		PRINT_ERROR("GHOST SPAWNED");
		PacGhostEnemy->OnPacManKilled.AddDynamic(this, &AMaze::ResetEnemyKilled);
		PacGhostEnemy->OnPacManKilled.AddDynamic(this->Audio, &ASoundManager::PacManGhostEat);
		Enemies.Add(PacGhostEnemy);
		SpawnCounter--;
	}
}
