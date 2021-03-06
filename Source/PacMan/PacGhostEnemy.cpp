// Fill out your copyright notice in the Description page of Project Settings.


#include "PacGhostEnemy.h"
#include "Components/CapsuleComponent.h"
#include "GhostCharacter.h"

// Sets default values
APacGhostEnemy::APacGhostEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PacGhostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PacGhostmesh"));
	PacGhostMesh->SetupAttachment(RootComponent);

	

}

// Called when the game starts or when spawned
void APacGhostEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&APacGhostEnemy::OnOverlapBegin);
	
}

// Called every frame
void APacGhostEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacGhostEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APacGhostEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!OtherActor) return;
	if(OtherActor->IsA(AGhostCharacter::StaticClass()))
	{
		//If the player is invulnerable the ghost is killed instead of killing the player
		if(Cast<AGhostCharacter>(OtherActor)->IsPlayerInvulnerable())
		{
			OnPacManKilled.Broadcast(this);
		}
	}
}
// Called to kill the ghost ( the method is called when
//the player first active the "lightUp" skill.
//All ghost overlapping a certain radius are killed.
void APacGhostEnemy::KillGhost()
{
	OnPacManKilled.Broadcast(this);
}



