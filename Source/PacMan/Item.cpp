// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "GhostCharacter.h"

//Class representing collectable special items

AItem::AItem()
{
	
	PrimaryActorTick.bCanEverTick = true;
}

//Add a constant rotation to the item
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FRotator Rotation = FRotator(0.f, 10.f, 0.f);
	AddActorWorldRotation(Rotation * DeltaTime);
}
//Destroyed when overlapped by the player
void AItem::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!OtherActor) return;
	if(OtherActor->IsA(AGhostCharacter::StaticClass()))
	{
		Destroy();
	}
}
