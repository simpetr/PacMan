// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "PacGhostEnemy.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPacManKilled,AActor*, Ghost);
UCLASS()
class PACMAN_API APacGhostEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacGhostEnemy();
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Enemy settings")
	UStaticMeshComponent*  PacGhostMesh;

	UPROPERTY(BlueprintAssignable)
	FPacManKilled OnPacManKilled;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// declare overlap begin function
	UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void KillGhost();
};
