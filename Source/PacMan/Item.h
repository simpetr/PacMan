// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API AItem : public ACollectable
{
	GENERATED_BODY()


public:
	AItem();
	virtual void Tick(float DeltaTime) override;
	virtual void OnOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	
};
