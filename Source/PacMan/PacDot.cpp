// Fill out your copyright notice in the Description page of Project Settings.


#include "PacDot.h"
#include "GhostCharacter.h"

#define PRINT_ERROR(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Red,TEXT(text),false)
#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,TEXT(text),false)
#define PRINT_COMPLEX(x,...) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,FString::Printf(TEXT(x), __VA_ARGS__));}


void APacDot::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!OtherActor) return;;
	if(OtherActor->IsA(AGhostCharacter::StaticClass()))
	{
		PRINT("PacDot");
		Destroy();
	}
	
}

