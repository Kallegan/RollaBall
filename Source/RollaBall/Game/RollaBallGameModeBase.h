// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollaBallGameModeBase.generated.h"

class URollableWidget;

UCLASS()
class ROLLABALL_API ARollaBallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	int32 ItemsCollected = 0;
	int32 ItemsInLevel = 0;

	UPROPERTY(EditAnywhere, Category= "Widgets")
	TSubclassOf<class UUserWidget> GameWidgetClass;

	UPROPERTY()
	URollableWidget* GameWidget;

	
	virtual void BeginPlay() override;

	//updates gui.
	void UpdateItemText();


public:
	void ItemCollected();	
	
};
