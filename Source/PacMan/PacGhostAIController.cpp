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

//FOR DEBUG PURPOSES 
/*#define PRINT_ERROR(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,10.f, FColor::Red,TEXT(text),false)
#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,10.f, FColor::Green,TEXT(text),false)
#define PRINT_COMPLEX(x,...) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1,10.f, FColor::Green,FString::Printf(TEXT(x), __VA_ARGS__));}*/


void APacGhostAIController::BeginPlay()
{
	Super::BeginPlay();
}


void APacGhostAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	ControlledPawn = Cast<APacGhostEnemy>(InPawn);
	Player = Cast<AGhostCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		//Bind called when a player collect a special item
		Player->OnCollected.AddDynamic(this, &APacGhostAIController::ReactToPlayerAction);
	}
	UWorld* World = GetWorld();
	if(World)
	{
		NavMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
		if (NavMesh)
		{
			//Add some Randomness to the duration of the Chasing and Scattering Phase
			ChasingTime+= FMath::RandRange(-3,+3);
			ScatteringTime += FMath::RandRange(-3,+3);
			GetWorldTimerManager().SetTimer(TimerHandle, this, &APacGhostAIController::ScatterPhase, 2.f,false);
		}
		
	}
	
}

void APacGhostAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (Result.Code == (EPathFollowingResult::Aborted))
	{
		//if I am here I changed phase and my previous
		//movement has been deleted (for example I could not reach the player)
		//reset variable
		if(IsChasing) IsChasing = false;
		if(IsScattering) IsScattering = false;
		return;
	}
	//I reached the point..
	if(Result.Code == (EPathFollowingResult::Success))
	{
		//..but I'm not in chasing mode
		if( IsScattering && !IsChasing)
		{
			//if I'm close
			const FVector ControlledLocation = ControlledPawn->GetActorLocation();
			const FVector PlayerLocation = Player->GetActorLocation();
			if(FVector::Distance(ControlledLocation,PlayerLocation)<= 700.f)
			{
				//switch immediately to chasing mode
				ChasingPhase();
			}else
			{
				//otherwise nomal scattering mode
				ScatterPhase();
			}
		}
	}
	
}

void APacGhostAIController::ScatterPhase()
{
	FNavLocation RandomLocation;
	const FVector AILocation = ControlledPawn->GetActorLocation();
	if (NavMesh)
	{
		//Find and reach a point around me
		if (NavMesh->GetRandomReachablePointInRadius(AILocation, 600.f, RandomLocation))
		{
			MoveToLocation(RandomLocation.Location);
		}
	}
	//Set the Timer after which i start the chasing phase
	//If I haven't set it yet
	if (!IsScattering)
	{
		IsScattering = true;
		IsChasing = false;
		GetWorldTimerManager().ClearTimer(PhaseHandle);
		GetWorldTimerManager().SetTimer(PhaseHandle, this, &APacGhostAIController::ChasingPhase, ScatteringTime,
		                                false);
		
	}
}

void APacGhostAIController::ChasingPhase()
{
	//In the chasing phase the enemy will trye to reach the player
	IsScattering = false;
	IsChasing = true;
	if (NavMesh)
	{
		MoveToActor(Player, 8.f, false);
	}
	//After a certain time i switch back to the scattering phase
	GetWorldTimerManager().ClearTimer(PhaseHandle);
	GetWorldTimerManager().SetTimer(PhaseHandle, this, &APacGhostAIController::ScatterPhase, ChasingTime, false);
}

//When the Player collect a Special Item the Chasing and Scattering time are updated
//More Special Item are collected more time the Enemies will spend in Chasing time
void APacGhostAIController::ReactToPlayerAction(int TypeCollected, int Value)
{
	if (TypeCollected == 1)
	{
		if(ScatteringTime !=2)
		{
			ScatteringTime -= 1;
		}
		ChasingTime += 1;
	}
}
