// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maze.generated.h"


class ACollectable;
class ATeleport;
class AGhostCharacter;
class APacGhostEnemy;
class ASoundManager;
UCLASS()
class PACMAN_API AMaze : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaze();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void SpawnStaticMeshActor(const FVector& InLocation) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	int XSize=1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	int YSize=1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	int Offset=100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	float ScaleFactor=20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	FString LevelSeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	UStaticMesh* Wall;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MazeSetup")
	TSubclassOf<AActor> MazeExit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	TSubclassOf<ACollectable> PacDot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	TSubclassOf<ACollectable> Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	TSubclassOf<ATeleport>  Teleport;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	TSubclassOf<APawn> Ghost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	TSubclassOf<APawn> PacGhost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	TSubclassOf<ASoundManager> AudioManager;
	

private:
	TArray<APacGhostEnemy*> Enemies;
	TArray<FVector> EnemiesSpawn;
	UPROPERTY()
	AGhostCharacter* Player;
	UPROPERTY()
	ASoundManager* Audio;
	FVector PlayerSpawn;
	FTimerHandle EnemySpawnHandle;
	FTimerHandle ResetHandle;
	int SpawnCounter;

	UFUNCTION()
	void ResetNotification(int Value);
	void ResetPosition();
	UFUNCTION()
	void ResetEnemyKilled(AActor* Enemy);
	UFUNCTION()
	void SpawnPacManGhost();
};
