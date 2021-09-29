// Fill out your copyright notice in the Description page of Project Settings.


#include "PacDotWidget.h"

UPacDotWidget::UPacDotWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

//Similar to BeginPlay
void UPacDotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPacDotWidget::UpdateCount(int Value)
{
	if(TextCounter)
	{
		if(TextCounter->Visibility == ESlateVisibility::Hidden)
		{
			TextCounter->SetVisibility(ESlateVisibility::Visible);
		}

		TextCounter->SetText(FText::FromString("Dots Counter: "+FString::FromInt(Value)));
	}
}

void UPacDotWidget::ResetText()
{
	if(TextCounter)
	{
		TextCounter->SetVisibility(ESlateVisibility::Hidden);
	}
}
