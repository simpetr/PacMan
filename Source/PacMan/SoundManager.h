// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundManager.generated.h"


UCLASS()
class PACMAN_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundManager();
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UAudioComponent* MainAudio;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Audiotrack")
	USoundBase* EatDot;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Audiotrack")
	USoundBase* EatItem;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Audiotrack")
	USoundBase* EatPacGhost;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Audiotrack")
	USoundBase* GotEat;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Audiotrack")
	USoundBase* GameOver;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Audiotrack")
	USoundBase* Notification;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Audiotrack")
	USoundBase* BackgroundMusic;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Settings")
	int GhostLife=3;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Settings")
	int ItemToCollect=4;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Settings")
	int Volume=0.8f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SomethingEat(int TypeCollected, int Value);
	UFUNCTION()
    void CheckGameOver(int Value);
	UFUNCTION()
	void PacManGhostEat(AActor* Enemy);
};
