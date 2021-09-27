// Fill out your copyright notice in the Description page of Project Settings.


#include "PacDot.h"

#define PRINT_ERROR(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Red,TEXT(text),false)
#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,TEXT(text),false)
#define PRINT_COMPLEX(x,...) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,FString::Printf(TEXT(x), __VA_ARGS__));}
// Sets default values
APacDot::APacDot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	
	DotMesh = CreateDefaultSubobject<UStaticMeshComponent>("Dot");
	DotMesh->SetupAttachment(Root);

	OnActorBeginOverlap.AddDynamic(this,&APacDot::OnOverlap);

}

// Called when the game starts or when spawned
void APacDot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APacDot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APacDot::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

	Destroy();
}

