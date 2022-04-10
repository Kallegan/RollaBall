// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallGameModeBase.h"
#include "RollableWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "RollaBall/Items/RollaBallItemBase.h"

void ARollaBallGameModeBase::BeginPlay()
{	//type array of actors.
	TArray<AActor*> Items;
	//Gets all static items in current level that is of ARollaBallItemBase, and store them in a list of the items.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollaBallItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();

	if(GameWidgetClass)
	{
		GameWidget = Cast<URollableWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if(GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}	
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
