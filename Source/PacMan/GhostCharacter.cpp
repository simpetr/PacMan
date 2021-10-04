// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "DrawDebugHelpers.h"
#include "Collectable.h"
#include "PacDot.h"
#include "GlowingDot.h"
#include "PacGhostEnemy.h"
#include "Kismet/KismetSystemLibrary.h"

#define PRINT_ERROR(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Red,TEXT(text),false)
#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,TEXT(text),false)
#define PRINT_COMPLEX(x,...) if (GEngine) {GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Green,FString::Printf(TEXT(x), __VA_ARGS__));}

// Sets default values
AGhostCharacter::AGhostCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 420;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	GhostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	GhostMesh->SetupAttachment(RootComponent);
	GhostVisionArea = CreateDefaultSubobject<UPointLightComponent>("GhostVision");
	GhostVisionArea->SetupAttachment(GhostMesh);
	

	BaseTurnRate = 45.f;
	BaseLookUpAtRate = 45.f;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&AGhostCharacter::OnOverlapBegin);

}

bool AGhostCharacter::IsSkillActive() const
{
	return IsPressed;
}

// Called when the game starts or when spawned
void AGhostCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*Setting up light parameters*/
	GhostVisionArea->SetIntensityUnits(ELightUnits::Candelas);
	GhostVisionArea->SetIntensity(3.f);
	GhostVisionArea->SetAttenuationRadius(220.f);
	GhostVisionArea->SetSourceRadius(200.f);
	GhostVisionArea->SetSoftSourceRadius(200.f);
	GhostVisionArea->SetCastShadows(false);
	GhostVisionArea->bUseTemperature = true;
	GhostVisionArea->SetTemperature(12000);
	GhostVisionArea->SetMobility(EComponentMobility::Movable);

	/*Retrieving ScaryGhostmesh*/
	ScaredGhostMesh = GhostMesh->GetStaticMesh();

	
	
}

/*Movement functions derived by the character class*/
#pragma region Movement


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
#pragma endregion Movement

void AGhostCharacter::Fire()
{
	if(AvailableDot>=SkillA)
	{
		PRINT("Fire");
		AvailableDot-=SkillA;
		OnCollected.Broadcast(0,AvailableDot);
		//DO SOMETHING
		/*FVector Loc;
		FRotator Rot;
		GetController()->GetPlayerViewPoint(Loc,Rot);*/
		const FVector Loc = GetActorForwardVector();
		const FVector LocStart = GetActorLocation();
		//Debug Purposes
		DrawDebugSphere(GetWorld(),LocStart,5,8,FColor::Red,false,3,0,1);
		DrawDebugLine(GetWorld(),LocStart,LocStart+(Loc*100.f),FColor::Red,false,3,0,1);
		if(GlowingDot)
		{
			FActorSpawnParameters SpawnParameters;
			AGlowingDot* Sphere =  GetWorld()->SpawnActor<AGlowingDot>(GlowingDot,LocStart,GetActorRotation(),SpawnParameters);
		}
		
		
		
	}
}

//TODO change with light immdiately and then lerp
void AGhostCharacter::LightUp()
{
	if(AvailableDot>=SkillB)
	{
		
		PRINT("Light Up");
		AvailableDot-=SkillB;
		OnCollected.Broadcast(0,AvailableDot);
		
		GhostMesh->SetStaticMesh(NormalGhost);
		ElapsedTme = 0.f;
		SkillEnd = false;
		ColorStart = GhostVisionArea->Temperature;
		ColorEnd = 3500;
		IntensityStart = GhostVisionArea->Intensity;
		IntensityEnd =10;
		IsPressed = true;
		//GetWorldTimerManager().SetTimer(TimerHandle,this,&AGhostCharacter::StopSkill,2.f,false,2.f);
		/*Actors I want overlapping with the sphere*/
		TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectType;
		TraceObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
		/*Ignore these actors*/
		TArray<AActor*> IgnoreActors;
		IgnoreActors.Add(this);
		TArray<AActor*> InsideSphere;
		UClass* SeekClass = APacGhostEnemy::StaticClass();
		
		
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(),GetActorLocation(),150.f,TraceObjectType,SeekClass,IgnoreActors,InsideSphere);
		PRINT_COMPLEX("%d", InsideSphere.Num());
		for(auto& x : InsideSphere)
		{
			x->Destroy();
		}
	}
}

// Called every frame
void AGhostCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsPressed)
	{
		GhostVisionArea->SetIntensity(FMath::Lerp(IntensityStart,IntensityEnd,ElapsedTme/LerpDuration));
		GhostVisionArea->SetTemperature(FMath::Lerp(ColorStart,ColorEnd,ElapsedTme/LerpDuration));
		ElapsedTme+=DeltaTime;
		if(ElapsedTme>=LerpDuration)
			StopSkill();
	}
	

}

// Called to bind functionality to input
void AGhostCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AGhostCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGhostCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGhostCharacter::TurnAtRate);

	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&AGhostCharacter::Fire);
	PlayerInputComponent->BindAction("LightUp",IE_Pressed,this,&AGhostCharacter::LightUp);
	/*PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGhostCharacter::LookUpAtRate);*/
}

void AGhostCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(!OtherActor) return;
	if(OtherActor->IsA(ACollectable::StaticClass()))
	{
		if(OtherActor->IsA(APacDot::StaticClass()))
		{
			CollectedDot++;
			AvailableDot++;
			OnCollected.Broadcast(0, AvailableDot);
		}else
		{
			CollectedItem++;
			OnCollected.Broadcast(1,CollectedItem);
		}
		return;
	}
	if(OtherActor->IsA(APacGhostEnemy::StaticClass()))
	{
		
		OnEat.Broadcast(0);
	}

	
}

void AGhostCharacter::StopSkill()
{
	PRINT("CALLED STOP");
	//TODO invert condition for better reading
	if(!SkillEnd)
	{
		ColorStart = GhostVisionArea->Temperature;
		ColorEnd = 12000;
		IntensityStart = GhostVisionArea->Intensity;
		IntensityEnd = 3;
		
		
		ElapsedTme = 0.f;
		SkillEnd = true;
	}
	else
	{
		GhostMesh->SetStaticMesh(ScaredGhostMesh);
		IsPressed = false;
	}
	
	
}

