// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeExit.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
UCLASS()
class PACMAN_API AMazeExit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeExit();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UBoxComponent* Box;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/*UFUNCTION()
	virtual void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
