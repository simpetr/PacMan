// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Collectable.h"
#include "GameFramework/Actor.h"
#include "PacDot.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class USphereComponent;
UCLASS()
class PACMAN_API APacDot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APacDot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* DotMesh;

	UFUNCTION()
    void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);
	

};
