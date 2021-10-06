// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlowingDot.generated.h"

//Class representig a glowing dot that move in a straight line
class UStaticMeshComponent;
class USceneComponent;
class UPointLightComponent;
UCLASS()
class PACMAN_API AGlowingDot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlowingDot();

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

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UPointLightComponent* LightArea;

	UFUNCTION()
    virtual void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float Speed = 240.f;
};
