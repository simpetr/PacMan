// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManHUD.h"

#include "PacDotWidget.h"
#include "ItemWidget.h"
#include "GhostCharacter.h"
#include "SkillsWidget.h"
#include "Blueprint/UserWidget.h"

APacManHUD::APacManHUD()
{
}

void APacManHUD::DrawHUD()
{
	Super::DrawHUD();
}

void APacManHUD::BeginPlay()
{
	Super::BeginPlay();

	if(ItemWidget && DotWidget && SkillsWidget)
	{
		PacDot = CreateWidget<UPacDotWidget>(GetWorld(),DotWidget);
		Item = CreateWidget<UItemWidget>(GetWorld(),ItemWidget);
		Skills = CreateWidget<USkillsWidget>(GetWorld(),SkillsWidget);
		if(PacDot&&Item&&Skills)
		{
			PacDot->AddToViewport();
			Item->AddToViewport();
			Skills->AddToViewport();
		}
	}

	AGhostCharacter* Player = Cast<AGhostCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if(Player)
	{
		Player->OnCollected.AddDynamic(this,&APacManHUD::UpdateUI);
	}
}

void APacManHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//TODO change with an Enum
void APacManHUD::UpdateUI(int TypeCollected, int Value)
{
	switch (TypeCollected)
	{
		case 0:
			PacDot->UpdateCount(Value);
			Skills->EnableSkills(Value);
			break;
		case 1:
			Item->UpdateCount(Value);
			break;
		default:
			break;
	}

	
}
