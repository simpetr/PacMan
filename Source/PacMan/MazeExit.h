// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GhostCharacter.h"
#include "GameFramework/Actor.h"
#include "MazeExit.generated.h"

class UStaticMeshComponent;
UCLASS()
class PACMAN_API AMazeExit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeExit();

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Settings")
	UStaticMeshComponent* MazeExit;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UFUNCTION()
    virtual void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	UPROPERTY();
	AGhostCharacter* Player;

};
