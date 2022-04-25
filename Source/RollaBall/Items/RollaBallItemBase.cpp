// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallItemBase.h"
#include "RollaBall/Game/RollaBallGameModeBase.h"
#include "RollaBall/Game/RollaBallPlayer.h"



// Sets default values
ARollaBallItemBase::ARollaBallItemBase()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARollaBallItemBase::OverlapBegin);
}


void ARollaBallItemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if casting to player isnt null
	if(Cast<ARollaBallPlayer>(OtherActor) != nullptr)
	{
		Collected();
	}
}

void ARollaBallItemBase::Collected_Implementation()
{
	if(ARollaBallGameModeBase* GameMode = Cast<ARollaBallGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->ItemCollected();
	}
}
