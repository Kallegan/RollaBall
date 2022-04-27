// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollaBallPlayer.h"
#include "RollaBallGameModeBase.generated.h"


class URollableWidget;
UCLASS()
class ROLLABALL_API ARollaBallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	
public:
	ARollaBallGameModeBase();
	
	UPROPERTY()
	ARollaBallPlayer* MyCharacter;

	UPROPERTY(EditDefaultsOnly)
	int ResetCount = 2;

private:
		
	virtual void Tick(float DeltaSeconds) override;
	
protected:

	int ItemsCollected = 0;
	int ItemsInLevel = 0;
	int CoinScore = 0;
	
	
	float CurrentSupercharge = 0;
	float MaxSuperCharge = 0;
	

	UPROPERTY(EditAnywhere, Category= "Widgets")
	TSubclassOf<UUserWidget> GameWidgetClass;

	UPROPERTY()
	URollableWidget* GameWidget;
	
	virtual void BeginPlay() override;	

	//updates gui.
	void UpdateItemText();

public:
	void ItemCollected();
	void CoinCollected();
	void UpdateSupercharge();
	void PlayerResetPosition();
	
};
