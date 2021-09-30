// Fill out your copyright notice in the Description page of Project Settings.


#include "PacDotWidget.h"

UPacDotWidget::UPacDotWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

//Similar to BeginPlay
void UPacDotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateCount(0);
}

void UPacDotWidget::UpdateCount(int Value) const
{
	if(TextCounter)
	{
		if(TextCounter->Visibility == ESlateVisibility::Hidden)
		{
			TextCounter->SetVisibility(ESlateVisibility::Visible);
		}

		TextCounter->SetText(FText::FromString("Dots: "+FString::FromInt(Value)));
	}
}
