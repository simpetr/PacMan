// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillsWidget.h"

USkillsWidget::USkillsWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void USkillsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TextPacDotNeedA->SetText(FText::FromString(FString::FromInt(PacDotSkillA)));
	TextPacDotNeedB->SetText(FText::FromString(FString::FromInt(PacDotSkillB)));
	EnableSkills(0);
}

void USkillsWidget::EnableSkills(int Value) const
{
	if(Value >= PacDotSkillA)
		ImageAlphaA->SetOpacity(0.f);
	else
		ImageAlphaA->SetOpacity(0.5f);
		
	if(Value >= PacDotSkillB)
		ImageAlphaB->SetOpacity(0.f);
	else
		ImageAlphaB->SetOpacity(0.5f);
}
