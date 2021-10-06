// Fill out your copyright notice in the Description page of Project Settings.


#include "PacDot.h"
#include "GhostCharacter.h"

//Destroyed when overlapped by the player
void APacDot::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!OtherActor) return;;
	if(OtherActor->IsA(AGhostCharacter::StaticClass()))
	{
		Destroy();
	}
	
}

