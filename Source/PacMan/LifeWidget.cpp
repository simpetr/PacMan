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
//Update the text when the player is eaten by a ghost
// if the player has still life an animation is played.
// if the player has no life new UI elements become visible
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

//called when the player click on the restart button
void ULifeWidget::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, *GetWorld()->GetName(), true);
}
