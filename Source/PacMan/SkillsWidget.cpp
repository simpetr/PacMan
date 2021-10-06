// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillsWidget.h"

USkillsWidget::USkillsWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void USkillsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TextPacDotNeedA->SetText(FText::FromString("Dots: "+ FString::FromInt(PacDotSkillA)));
	TextPacDotNeedB->SetText(FText::FromString("Dots: "+FString::FromInt(PacDotSkillB)));
	CheckSkills(0);
}

void USkillsWidget::CheckSkills(int Value) const
{
	TextCounter->SetText(FText::FromString("Dots: "+FString::FromInt(Value)));
	if(Value >= PacDotSkillA)
		ImageAlphaA->SetOpacity(0.f);
	else
		ImageAlphaA->SetOpacity(0.5f);
		
	if(Value >= PacDotSkillB)
		ImageAlphaB->SetOpacity(0.f);
	else
		ImageAlphaB->SetOpacity(0.5f);
}
