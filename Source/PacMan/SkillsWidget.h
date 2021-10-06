// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "SkillsWidget.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API USkillsWidget : public UUserWidget
{
	GENERATED_BODY()

	
	public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Settings")
	int PacDotSkillA=5;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Settings")
	int PacDotSkillB=20;
	
	USkillsWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void CheckSkills(int Value) const;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* TextSkillDigitA;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* TextPacDotNeedA;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* TextSkillNameA;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UImage* ImageAlphaA;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* TextSkillDigitB;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* TextPacDotNeedB;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* TextSkillNameB;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UImage* ImageAlphaB;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* TextCounter;
	
};
