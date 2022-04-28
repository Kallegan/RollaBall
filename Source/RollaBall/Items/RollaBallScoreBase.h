#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollaBallScoreBase.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class ROLLABALL_API ARollaBallScoreBase : public AActor
{
	GENERATED_BODY()
public:
	ARollaBallScoreBase();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Components")
	USphereComponent* Sphere;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

protected:
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintNativeEvent, Category= "Collects")
	void Collected();
};
