// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#define PRINT_ERROR(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Red,TEXT(text),false)
#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,TEXT(text),false)
#define PRINT_COMPLEX(x,...) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,FString::Printf(TEXT(x), __VA_ARGS__));}

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator Rotation = FRotator(0.f, 10.f, 0.f);
	AddActorWorldRotation(Rotation * DeltaTime);
}

void AItem::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	PRINT("Item");
	Destroy();
}
