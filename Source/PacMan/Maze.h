// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maze.generated.h"

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	int XSize=1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	int YSize=1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	int Offset=100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	float ScaleFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	FString LevelSeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	UStaticMesh* Wall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	UStaticMesh* PacDot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	UStaticMesh* Teleport;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	APawn* Ghost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MazeSetup")
	AActor* PacGhost;
};
