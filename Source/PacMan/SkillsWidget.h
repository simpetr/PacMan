// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "SkillsWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UImage;
UCLASS()
class PACMAN_API USkillsWidget : public UUserWidget
{
	GENERATED_BODY()

	
	public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Settings")
	int PacDotSkillA=5;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Settings")
	int PacDotSkillB=25;
	
	USkillsWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void CheckSkills(int Value) const;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	UTextBlock* TextSkillDigitA;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	UTextBlock* TextPacDotNeedA;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	UTextBlock* TextSkillNameA;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	UImage* ImageAlphaA;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	UTextBlock* TextSkillDigitB;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	UTextBlock* TextPacDotNeedB;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	UTextBlock* TextSkillNameB;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	UImage* ImageAlphaB;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	UTextBlock* TextCounter;
	
};
