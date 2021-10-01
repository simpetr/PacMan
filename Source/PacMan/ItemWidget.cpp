// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"


UItemWidget::UItemWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateCount(0);
	if(TextEscape)
		TextEscape->SetVisibility(ESlateVisibility::Hidden);
}

void UItemWidget::UpdateCount(int Value) const
{
	
	if(TextCounter)
	{
		TextCounter->SetText(FText::FromString("Collected Flagship: "+FString::FromInt(Value)+"/4"));
	}
	if(Value == 2 && TextEscape)
	{
		if(TextEscape->Visibility == ESlateVisibility::Hidden)
		{
			TextEscape->SetVisibility(ESlateVisibility::Visible);
		}

		TextEscape->SetText(FText::FromString("All flagships collected. Escape from the Maze!"));
	}
}
