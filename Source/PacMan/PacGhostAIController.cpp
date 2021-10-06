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
	PRINT("Begin play");
}


void APacGhostAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PRINT("POSSESED");
	ControlledPawn = Cast<APacGhostEnemy>(InPawn);
	Player = Cast<AGhostCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		Player->OnCollected.AddDynamic(this, &APacGhostAIController::ReactToPlayerAction);
	}
	UWorld* World = GetWorld();
	if(World)
	{
		NavMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
		if (NavMesh)
		{
			PRINT_COMPLEX("%s", *NavMesh->GetName());
		}
		ChasingTime+= FMath::RandRange(-3,+3);
		ScatteringTime += FMath::RandRange(-3,+2);
		GetWorldTimerManager().SetTimer(TimerHandle, this, &APacGhostAIController::ScatterPhase, 0.1f, false, 2.f);
	}
	
}

void APacGhostAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	//PRINT_COMPLEX("%s",*Result.ToString());
	/*GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorldTimerManager().SetTimer(TimerHandle,this,&APacGhostAIController::ScatterPhase,0.1f,false,0.2f);*/
	if (Result.Code == (EPathFollowingResult::Aborted))
	{
		PRINT_ERROR("RICERCA FALLITA VADO GIRANDO!");
		//Reaching actor failed
		if(IsChasing) IsChasing = false;
		if(IsScattering) IsScattering = false;
	}
	ScatterPhase();
}

void APacGhostAIController::ScatterPhase()
{
	PRINT("FASE DI SCATTER");
	FNavLocation RandomLocation;
	const FVector AILocation = ControlledPawn->GetActorLocation();
	//FVector RandomLocation = NavMesh->GetRandomReachablePointInRadius(this,ControlledPawn->GetActorLocation(),1000.f );
	if (NavMesh)
	{
		if (NavMesh->GetRandomReachablePointInRadius(AILocation, 600.f, RandomLocation))
			//DrawDebugSphere(GetWorld(), RandomLocation.Location, 20.f, 15, FColor::Red, false, 2);
		{
			MoveToLocation(RandomLocation.Location);
		}
	}

	if (!IsScattering)
	{
		//PRINT("SETTO CONTATORE");
		IsScattering = true;
		IsChasing = false;
		GetWorldTimerManager().ClearTimer(ChasingHandle);
		GetWorldTimerManager().SetTimer(ChasingHandle, this, &APacGhostAIController::ChasingPhase, ScatteringTime,
		                                false);
		
	}
}

void APacGhostAIController::ChasingPhase()
{
	PRINT("FASE DI CHASING");
	IsScattering = false;
	IsChasing = true;
	if (NavMesh)
	{
		MoveToActor(Player, 8.f, false);
	}
	//GetWorldTimerManager().ClearTimer(PhaseHandler);
	GetWorldTimerManager().ClearTimer(ChasingHandle);
	GetWorldTimerManager().SetTimer(ChasingHandle, this, &APacGhostAIController::ScatterPhase, ChasingTime, false);
}

void APacGhostAIController::ReactToPlayerAction(int TypeCollected, int Value)
{
	if (TypeCollected == 1)
	{
		if(ScatteringTime !=1)
		{
			ScatteringTime -= 1;
		}
		ChasingTime += 1;
	}
}
