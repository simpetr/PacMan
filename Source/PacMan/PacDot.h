// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "PacDot.generated.h"
//Class representing collectable yellow dots
UCLASS()
class PACMAN_API APacDot : public ACollectable
{
	GENERATED_BODY()

public:
    virtual void OnOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	

};
