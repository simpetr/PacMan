// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "LifeWidget.generated.h"

/**
 * 
 */

UCLASS()
class PACMAN_API ULifeWidget : public UUserWidget
{
	GENERATED_BODY()


private:
	UFUNCTION()
	void RestartLevel();

public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Settings")
	int GhostLife=3;
	
	ULifeWidget(const FObjectInitializer& ObjectInitializer);

	virtual  void NativeConstruct() override;

	bool CheckGameOver(int Value);


	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* TextLife;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* TextGameOver;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	class UButton* ButtonRestart;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	class UImage* BackGround;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Transient, meta = ( BindWidgetAnim ) )
	class UWidgetAnimation* RestartFading;
	
};
