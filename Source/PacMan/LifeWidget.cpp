// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeWidget.h"


ULifeWidget::ULifeWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

void ULifeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (TextLife)
	{
		TextLife->SetText(FText::FromString("Life: " + FString::FromInt(GhostLife)));
	}
	if (TextGameOver && ButtonRestart)
	{
		BackGround->SetVisibility(ESlateVisibility::Hidden);
		TextGameOver->SetVisibility(ESlateVisibility::Hidden);
		ButtonRestart->SetVisibility(ESlateVisibility::Hidden);
		ButtonRestart->OnClicked.AddDynamic(this, &ULifeWidget::RestartLevel);
	}
}

bool ULifeWidget::CheckGameOver(int Value)
{
	TextLife->SetText(FText::FromString("Life: " + FString::FromInt(Value)));

	if (Value == 0)
	{
		TextLife->SetVisibility(ESlateVisibility::Hidden);


		TextGameOver->SetVisibility(ESlateVisibility::Visible);


		ButtonRestart->SetVisibility(ESlateVisibility::Visible);


		BackGround->SetVisibility(ESlateVisibility::Visible);
		return true;
	}else
	{
		PlayAnimation(RestartFading);
	}
	return false;
}


void ULifeWidget::RestartLevel()
{
	//TODO Change restart point? 
	UGameplayStatics::OpenLevel(this, *GetWorld()->GetName(), true);
}
