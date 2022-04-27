#include "RollaBallScoreBase.h"
#include "RollaBall/Game/RollaBallGameModeBase.h"
#include "Components/SphereComponent.h"
#include "RollaBall/Game/RollaBallPlayer.h"

// Sets default values
ARollaBallScoreBase::ARollaBallScoreBase()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	RootComponent = Sphere;
	Mesh->SetupAttachment(Sphere);	

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARollaBallScoreBase::OverlapBegin);
}


void ARollaBallScoreBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if casting to player isnt null
	if(Cast<ARollaBallPlayer>(OtherActor) != nullptr)	
		Collected();
}

void ARollaBallScoreBase::Collected_Implementation()
{	
	if(ARollaBallGameModeBase* GameMode = Cast<ARollaBallGameModeBase>(GetWorld()->GetAuthGameMode()))	
		GameMode->CoinCollected();			
}
