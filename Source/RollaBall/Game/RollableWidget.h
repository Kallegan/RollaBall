// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "RollableWidget.generated.h"

class ARollaBallPlayer;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS() //make abstract
class ROLLABALL_API URollableWidget : public UUserWidget
{
	GENERATED_BODY()	

public:	
	
	//adding the collect text by using event triggered by game manager.
	UFUNCTION(BlueprintImplementableEvent)
	void SetItemText(int ItemsCollected, int ItemsInLevel);
	
	void SetCurrentCharge(float CurrentCharge, float MaxCharge);	
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* SuperchargeBar;		
};
