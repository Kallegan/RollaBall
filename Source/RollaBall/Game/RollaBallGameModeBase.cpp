// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallGameModeBase.h"
#include "RollableWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "RollaBall/Items/RollaBallItemBase.h"


void ARollaBallGameModeBase::BeginPlay()
{	
	Super::BeginPlay();	

	MyCharacter = Cast<ARollaBallPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
	MaxSuperCharge = MyCharacter->GetMaxCharge();
	
	//type array of actors.
	TArray<AActor*> Items;
	//Gets all static items in current level that is of ARollaBallItemBase, and store them in a list of the items.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollaBallItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();
	
	GameWidget = Cast<URollableWidget>(CreateWidget(GetWorld(), GameWidgetClass));
	
	if(GameWidgetClass)
	{				
		if(GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
			GameWidget->SetPlayerResetRemaning(ResetCount);
		}
	}	
}

ARollaBallGameModeBase::ARollaBallGameModeBase()
{	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ARollaBallGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);	
	UpdateSupercharge();	
}

void ARollaBallGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void ARollaBallGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}

void ARollaBallGameModeBase::UpdateSupercharge()
{	
	CurrentSupercharge = MyCharacter->GetCurrentSupercharge();
	MaxSuperCharge = MyCharacter->GetMaxCharge();
	GameWidget->SetCurrentCharge(CurrentSupercharge, MaxSuperCharge);
}

void ARollaBallGameModeBase::PlayerResetPosition()
{
	if(ResetCount > 0)
	{
		ResetCount--;
		GameWidget->SetPlayerResetRemaning(ResetCount);
	}	
}


