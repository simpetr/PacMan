// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AGhostCharacter::AGhostCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 200;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	GhostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	GhostMesh->SetupAttachment(RootComponent);

	BaseTurnRate = 45.f;
	BaseLookUpAtRate = 45.f;

}

// Called when the game starts or when spawned
void AGhostCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGhostCharacter::MoveForward(float Value)
{
	if(Controller && (Value !=0.f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		//Y
		
		const FRotator YawRotation = FRotator(0.f,Rotation.Yaw,0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction,Value);
		
	}
}

void AGhostCharacter::MoveRight(float Value)
{
	if(Controller && (Value !=0.f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		//Y
		const FRotator YawRotation = FRotator(0.f,Rotation.Yaw,0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction,Value);
		
	}
}

void AGhostCharacter::TurnAtRate(float Value)
{
	//AddControllerYawInput(Value * BaseTurnRate* GetWorld()->GetDeltaSeconds());
	
	AddControllerYawInput(Value * BaseTurnRate* GetWorld()->GetDeltaSeconds());
}

void AGhostCharacter::LookUpAtRate(float Value)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Value * BaseLookUpAtRate * GetWorld()->GetDeltaSeconds());
}

// Called every frame
void AGhostCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGhostCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AGhostCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGhostCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGhostCharacter::TurnAtRate);
	/*PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGhostCharacter::LookUpAtRate);*/
}

