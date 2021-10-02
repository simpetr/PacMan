// Fill out your copyright notice in the Description page of Project Settings.


#include "GlowingDot.h"
#include "Components/PointLightComponent.h"
#include "Engine/StaticMeshActor.h"


#define PRINT_ERROR(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Red,TEXT(text),false)
#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,TEXT(text),false)
#define PRINT_COMPLEX(x,...) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,FString::Printf(TEXT(x), __VA_ARGS__));}
// Sets default values
AGlowingDot::AGlowingDot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Dot");
	Mesh->SetupAttachment(Root);

	LightArea = CreateDefaultSubobject<UPointLightComponent>("LightArea");
	LightArea->SetupAttachment(RootComponent);
	

	OnActorBeginOverlap.AddDynamic(this,&AGlowingDot::OnOverlap);

}

// Called when the game starts or when spawned
void AGlowingDot::BeginPlay()
{
	Super::BeginPlay();
	LightArea->SetIntensityUnits(ELightUnits::Candelas);
	LightArea->SetIntensity(2.5f);
	LightArea->SetAttenuationRadius(200.f);
	LightArea->SetSourceRadius(200.f);
	LightArea->SetSoftSourceRadius(200.f);
	LightArea->SetCastShadows(false);
	//TODO tune color, in bluprint the light is set to yellow
	LightArea->bUseTemperature = true;
	LightArea->SetTemperature(12000);
	LightArea->SetMobility(EComponentMobility::Movable);
	
}

// Called every frame
void AGlowingDot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector Pos = GetActorLocation() + (GetActorForwardVector()* DeltaTime * Speed);
	SetActorLocation(Pos);

}

void AGlowingDot::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	PRINT("INSIDE");
	if(!OtherActor) return;
	if(OtherActor->IsA(AStaticMeshActor::StaticClass()))
	{
		Destroy();
	}
}
