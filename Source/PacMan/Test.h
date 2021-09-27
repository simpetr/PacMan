// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacDot.h"
#include "Test.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API ATest : public APacDot
{
	GENERATED_BODY()

public:
	virtual void OnOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
};
