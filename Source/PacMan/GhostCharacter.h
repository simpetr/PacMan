// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GhostCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class UPointLightComponent;
class AGlowingDot;
class USoundBase;
class UStaticMesh;

//Delegate called when a dot or special item is collected or consumed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCollectedElement, int, TypeCollected, int , Value);
//Delegate called when the player is eaten
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerEaten, int, Life);
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

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Player")
	UPointLightComponent*  GhostVisionArea;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Player")
	TSubclassOf<AGlowingDot> GlowingDot;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Player")
	UStaticMesh* NormalGhost;

	UPROPERTY(BlueprintAssignable)
	FCollectedElement OnCollected;
	
	UPROPERTY(BlueprintAssignable)
	FPlayerEaten OnEat;

	bool IsPlayerInvulnerable() const;
	int GetItem() const;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Settings")
	int GhostLife = 3;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Settings")
	int SkillA = 5;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Settings")
	int SkillB = 20;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Value);

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Player")
	float BaseTurnRate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// declare overlap begin function
	UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	void Fire();
	void LightUp();
	
	int AvailableDot = 0;
	int CollectedItem = 0;
	
	bool IsPressed = false;
	bool IsInvulnerable = false;

	float LerpDuration = 1.5f;
	float ElapsedTme =0.f;
	int ColorStart;
	int ColorEnd;
	int IntensityStart;
	int IntensityEnd;
	int AttenuationRadiusStart;
	int AttenuationRadiusEnd;
	
	UPROPERTY()
	UStaticMesh* ScaredGhostMesh;

	FTimerHandle TimerHandle;

	void StopSkill();
	void RevertLight();
};
