// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "PacDotWidget.generated.h"


UCLASS()
class PACMAN_API UPacDotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPacDotWidget(const FObjectInitializer& ObjectInitializer);

	virtual  void NativeConstruct() override;

	void UpdateCount(int Value);

	void ResetText();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* TextCounter;
	
};
