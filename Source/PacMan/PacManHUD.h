// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PacManHUD.generated.h"

/**
 * 
 */
class UPacDotWidget;
class UItemWidget;
class USkillsWidget;
class ULifeWidget;
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
	TSubclassOf<UUserWidget> ItemWidget;
	UPROPERTY(EditDefaultsOnly,Category = "Widgets")
	TSubclassOf<UUserWidget> DotWidget;
	UPROPERTY(EditDefaultsOnly,Category = "Widgets")
	TSubclassOf<UUserWidget> SkillsWidget;
	UPROPERTY(EditDefaultsOnly,Category = "Widgets")
	TSubclassOf<UUserWidget> LifeWidget;
	
	UFUNCTION()
	void UpdateUI(int TypeCollected, int Value);
	UFUNCTION()
	void CheckGameOver(int Value);


private:
	UPROPERTY();
	UPacDotWidget* PacDot;
	UPROPERTY();
	UItemWidget* Item;
	UPROPERTY()
	USkillsWidget* Skills;
	UPROPERTY()
	ULifeWidget* GameOver;
};
