// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Dot");
	Mesh->SetupAttachment(Root);

	OnActorBeginOverlap.AddDynamic(this,&ACollectable::OnOverlap);

}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectable::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}

