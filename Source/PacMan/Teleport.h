// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleport.generated.h"

class UBoxComponent;
UCLASS()
class PACMAN_API ATeleport : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleport();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UBoxComponent* BoxCollider;

	void SetTeleportDirection(const FVector& Offset);
	
	UFUNCTION()
    void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	FVector Connection;	

};
