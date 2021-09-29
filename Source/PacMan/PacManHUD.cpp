// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManHUD.h"

#include "PacDotWidget.h"
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

	if(Widget)
	{
		PacDotWidget = CreateWidget<UPacDotWidget>(GetWorld(),Widget);
		if(PacDotWidget)
		{
			PacDotWidget->AddToViewport();
		}
	}
}

void APacManHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
