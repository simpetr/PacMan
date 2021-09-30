// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"


UItemWidget::UItemWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateCount(0);
}

void UItemWidget::UpdateCount(int Value) const
{
	if(TextCounter)
	{
		if(TextCounter->Visibility == ESlateVisibility::Hidden)
		{
			TextCounter->SetVisibility(ESlateVisibility::Visible);
		}

		TextCounter->SetText(FText::FromString("Collected Items: "+FString::FromInt(Value)+"/4"));
	}
}
