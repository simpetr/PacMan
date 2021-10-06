// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"
#include "GhostCharacter.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASoundManager::ASoundManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	MainAudio = CreateDefaultSubobject<UAudioComponent>("Audio");
	MainAudio->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ASoundManager::BeginPlay()
{
	Super::BeginPlay();
	MainAudio->SetSound(BackgroundMusic);
	MainAudio->Play();

	AGhostCharacter* Player = Cast<AGhostCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if(Player)
	{
		Player->OnCollected.AddDynamic(this,&ASoundManager::SomethingEat);
		Player->OnEat.AddDynamic(this,&ASoundManager::CheckGameOver);
	}
}

// Called every frame
void ASoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASoundManager::SomethingEat(int TypeCollected, int Value)
{
	switch (TypeCollected)
	{
	case 0:
		//Collected yellow dot
		UGameplayStatics::PlaySound2D(this, EatDot);
		break;
	case 1:
		//Collected item
		if (Value == ItemToCollect)
		{
			UGameplayStatics::PlaySound2D(this, Notification);
		}
		else
		{
			UGameplayStatics::PlaySound2D(this, EatItem);
		}

		break;
	default:
		break;
	}
}

void ASoundManager::CheckGameOver(int Value)
{
	if(Value == 0)
	{
		MainAudio->Stop();
		UGameplayStatics::PlaySound2D(this,GameOver);
	}else
	{
		UGameplayStatics::PlaySound2D(this,GotEat);
	}
}

void ASoundManager::PacManGhostEat(AActor* Enemy)
{
	UGameplayStatics::PlaySound2D(this,EatPacGhost);
}
