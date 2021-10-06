// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManHUD.h"

#include "PacDotWidget.h"
#include "ItemWidget.h"
#include "GhostCharacter.h"
#include "LifeWidget.h"
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
	//Create widgets
	if(ItemWidget && SkillsWidget && LifeWidget)
	{
		Fade = CreateWidget<UUserWidget>(GetWorld(),StartFade);
		Item = CreateWidget<UItemWidget>(GetWorld(),ItemWidget);
		Skills = CreateWidget<USkillsWidget>(GetWorld(),SkillsWidget);
		GameOver = CreateWidget<ULifeWidget>(GetWorld(),LifeWidget);
		
		if(Item && Skills && GameOver && Fade)
		{
			Fade->AddToViewport();
			Item->AddToViewport();
			Skills->AddToViewport();
			GameOver->AddToViewport();
		}
	}

	//Add Dynamic bind with the Player delegates
	AGhostCharacter* Player = Cast<AGhostCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if(Player)
	{
		Player->OnCollected.AddDynamic(this,&APacManHUD::UpdateUI);
		Player->OnEat.AddDynamic(this,&APacManHUD::CheckGameOver);
	}

	
}

//TODO change with an Enum
//Called when the player collect a yellow dot or a item.
void APacManHUD::UpdateUI(int TypeCollected, int Value)
{
	switch (TypeCollected)
	{
		case 0:
			//Collected yellow dot
			Skills->CheckSkills(Value);
			break;
		case 1:
			//Collected item
			Item->UpdateCount(Value);
			break;
		default:
			break;
	}	
}
//Called when the player is eaten by a ghost.
void APacManHUD::CheckGameOver(int Value)
{
	//if the player has no life anymore
	//hide all the widgets and active the
	//only UI mode
	if(GameOver->CheckGameOver(Value))
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if(PC)
		{
			Skills->SetVisibility(ESlateVisibility::Hidden);
			Item->SetVisibility(ESlateVisibility::Hidden);
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(GameOver->ButtonRestart->TakeWidget());
			//InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PC->SetInputMode(InputModeData);
			PC->bShowMouseCursor = true;
			PC->bEnableClickEvents = true;
			PC->bEnableMouseOverEvents = true;
		}
	}
}
