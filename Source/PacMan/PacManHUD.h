// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/HUD.h"
#include "PacManHUD.generated.h"

/**
 * 
 */
class UPacDotWidget;
UCLASS()
class PACMAN_API APacManHUD : public AHUD
{
	GENERATED_BODY()

public:
	APacManHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly,Category = "Widgets")
	TSubclassOf<UUserWidget> Widget;


private:
	UPROPERTY();
	UPacDotWidget* PacDotWidget;
	
};
