// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GhostCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCollectedElement, int, TypeCollected, int , Value);
UCLASS()
class PACMAN_API AGhostCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGhostCharacter();

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Camera")
	USpringArmComponent*  SpringArmComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Camera")
	UCameraComponent*  CameraComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Player")
	UStaticMeshComponent*  GhostMesh;

	UPROPERTY(BlueprintAssignable)
	FCollectedElement OnCollected;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Value);
	void LookUpAtRate(float Value);

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Player")
	float BaseTurnRate;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Player")
	float BaseLookUpAtRate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// declare overlap begin function
	UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	int CollectedDot = 0;
	int AvailableDot = 0;
	int CollectedItem = 0;
};
