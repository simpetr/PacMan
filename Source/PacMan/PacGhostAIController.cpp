// Fill out your copyright notice in the Description page of Project Settings.


#include "PacGhostAIController.h"
#include "GhostCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "PacGhostEnemy.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

#define PRINT_ERROR(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,10.f, FColor::Red,TEXT(text),false)
#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,10.f, FColor::Green,TEXT(text),false)
#define PRINT_COMPLEX(x,...) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1,10.f, FColor::Green,FString::Printf(TEXT(x), __VA_ARGS__));}

//TODO Improve AI add some randomness and reaction to light skill
void APacGhostAIController::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AGhostCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		Player->OnCollected.AddDynamic(this, &APacGhostAIController::ReactToPlayerAction);
	}
	NavMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	if (NavMesh)
	{
		PRINT_COMPLEX("%s", *NavMesh->GetName());
	}
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APacGhostAIController::ScatterPhase, 0.1f, false, 1.f);
}

void APacGhostAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	//PRINT_COMPLEX("%s",*Result.ToString());
	/*GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorldTimerManager().SetTimer(TimerHandle,this,&APacGhostAIController::ScatterPhase,0.1f,false,0.2f);*/
	if (Result.Code == (EPathFollowingResult::Aborted))
	{
		GetWorldTimerManager().ClearTimer(PhaseHandler);
		if (IsScattering) IsScattering = false;
	}
	ScatterPhase();
}

void APacGhostAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ControlledPawn = Cast<APacGhostEnemy>(InPawn);
}

void APacGhostAIController::ScatterPhase()
{
	PRINT("FASE DI SCATTER");
	FNavLocation RandomLocation;
	const FVector AILocation = ControlledPawn->GetActorLocation();
	//FVector RandomLocation = NavMesh->GetRandomReachablePointInRadius(this,ControlledPawn->GetActorLocation(),1000.f );
	NavMesh->GetRandomReachablePointInRadius(AILocation, 600.f, RandomLocation);
	DrawDebugSphere(GetWorld(), RandomLocation.Location, 20.f, 15, FColor::Red, false, 2);
	MoveToLocation(RandomLocation.Location);

	if (!IsScattering)
	{
		PRINT("DENTRO");
		GetWorldTimerManager().ClearTimer(PhaseHandler);
		GetWorldTimerManager().SetTimer(PhaseHandler, this, &APacGhostAIController::ChasingPhase, ScatteringTime, false);
		IsScattering = true;
		IsChasing = false;
	}
}

void APacGhostAIController::ChasingPhase()
{
	PRINT("FASE DI CHASING");
	IsScattering = false;
	IsChasing = true;
	MoveToActor(Player, 10.f, false);
	//GetWorldTimerManager().ClearTimer(PhaseHandler);
	GetWorldTimerManager().ClearTimer(PhaseHandler);
	GetWorldTimerManager().SetTimer(PhaseHandler, this, &APacGhostAIController::ScatterPhase, ChasingTime, false);
}

void APacGhostAIController::ReactToPlayerAction(int TypeCollected, int Value)
{
	if (TypeCollected == 1)
	{
		ScatteringTime-=1;
		ChasingTime+=1;
	}
}
