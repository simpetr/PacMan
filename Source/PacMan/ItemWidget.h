// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UItemWidget(const FObjectInitializer& ObjectInitializer);

	virtual  void NativeConstruct() override;

	void UpdateCount(int Value) const;

	void ResetText();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* TextCounter;
	
};
