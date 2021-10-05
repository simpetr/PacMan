// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GhostCharacter.h"
#include "PacGhostAIController.generated.h"

/**
 * 
 */
class UNavigationSystemV1;
class APacGhostEnemy;
UCLASS()
class PACMAN_API APacGhostAIController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	virtual void OnPossess(APawn* InPawn) override;
	void SetPhasesDuration(int Chasing, int Scattering);
	FTimerHandle TimerHandle;
	FTimerHandle PhaseHandler;

private:
	bool IsScattering = false;
	bool IsChasing = false;
	int ScatteringTime = 4;
	int ChasingTime = 10;
	UPROPERTY()
	AGhostCharacter* Player;
	UPROPERTY()
	APacGhostEnemy* ControlledPawn;
	UPROPERTY()
	UNavigationSystemV1* NavMesh;
	void ScatterPhase();
	void ChasingPhase();
	void ReactToPlayerAction(int TypeCollected, int Value);
};
