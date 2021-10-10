// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"


UItemWidget::UItemWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateCount(0);
	TextEscape->SetVisibility(ESlateVisibility::Hidden);
	PlayAnimation(StartFade);
}
//Update Text when an Item is collected. When all special items are collected
//an extra message appears
void UItemWidget::UpdateCount(int Value) const
{
	TextCounter->
		SetText(FText::FromString("Keys: " + FString::FromInt(Value) + "/" + FString::FromInt(ItemsToCollect)));

	if (Value == ItemsToCollect)
	{
		TextEscape->SetVisibility(ESlateVisibility::Visible);
		TextEscape->SetText(FText::FromString("All keys collected!\n\nEscape from the Maze\nReach the center!"));
	}
}
