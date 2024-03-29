// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollaBallItemBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class ROLLABALL_API ARollaBallItemBase : public AActor
{
	GENERATED_BODY()
	
public:		
	ARollaBallItemBase();
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

protected:	

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintNativeEvent, Category= "Collects")
	void Collected();
};
