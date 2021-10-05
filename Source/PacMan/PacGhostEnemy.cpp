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

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&APacGhostEnemy::OnOverlapBegin);

}

// Called when the game starts or when spawned
void APacGhostEnemy::BeginPlay()
{
	Super::BeginPlay();
	
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
		if(Cast<AGhostCharacter>(OtherActor)->IsSkillActive())
		{
			OnPacManKilled.Broadcast(this);
		}
	}
}

void APacGhostEnemy::KilledByLight()
{
	OnPacManKilled.Broadcast(this);
}



