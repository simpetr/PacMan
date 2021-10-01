// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeWidget.h"



ULifeWidget::ULifeWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void ULifeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(TextLife)
	{
		TextLife->SetText(FText::FromString("Life: "+FString::FromInt(GhostLife)));
	}
	if(TextGameOver&&ButtonRestart)
	{
		TextGameOver->SetVisibility(ESlateVisibility::Hidden);
		ButtonRestart->SetVisibility(ESlateVisibility::Hidden);
		ButtonRestart->OnClicked.AddDynamic(this,&ULifeWidget::RestartLevel);
	}
}

bool ULifeWidget::CheckGameOver(int Value)
{
	if(TextLife)
	{
		TextLife->SetText(FText::FromString("Life: "+FString::FromInt(Value)));
	}
	if(Value==0&&TextGameOver&&ButtonRestart)
	{
		if(TextGameOver->Visibility == ESlateVisibility::Hidden)
		{
			TextGameOver->SetVisibility(ESlateVisibility::Visible);
		}
		if(ButtonRestart->Visibility==ESlateVisibility::Hidden)
		{
			ButtonRestart->SetVisibility(ESlateVisibility::Visible);
		}
		return true;
	}
	return false;
}


void ULifeWidget::RestartLevel()
{
	//TODO Change restart point? 
	UGameplayStatics::OpenLevel(this,*GetWorld()->GetName(),true);
}