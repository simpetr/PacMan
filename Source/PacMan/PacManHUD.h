// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PacManHUD.generated.h"


class UItemWidget;
class USkillsWidget;
class ULifeWidget;
class USoundCue;
UCLASS()
class PACMAN_API APacManHUD : public AHUD
{
	GENERATED_BODY()

public:
	APacManHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,Category = "Widgets")
	TSubclassOf<UItemWidget> ItemWidget;
	UPROPERTY(EditDefaultsOnly,Category = "Widgets")
	TSubclassOf<USkillsWidget> SkillsWidget;
	UPROPERTY(EditDefaultsOnly,Category = "Widgets")
	TSubclassOf<ULifeWidget> LifeWidget;
	
	
	UFUNCTION()
	void UpdateUI(int TypeCollected, int Value);
	UFUNCTION()
	void CheckGameOver(int Value);


private:
	UPROPERTY();
	UItemWidget* Item;
	UPROPERTY()
	USkillsWidget* Skills;
	UPROPERTY()
	ULifeWidget* GameOver;

	
};
