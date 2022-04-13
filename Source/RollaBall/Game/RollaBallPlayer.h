// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RollaBallPlayer.generated.h"

class USpringArmComponent;	
class UCameraComponent;

UCLASS()
class ROLLABALL_API ARollaBallPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARollaBallPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;	

	UPROPERTY(EditDefaultsOnly)
	float MoveForce = 500.f;
	UPROPERTY(EditDefaultsOnly)
	float JumpImpulse = 100.f;
	int16 MaxJumpCount = 1;
	bool bHoldCamera = false;

	UPROPERTY()
	APlayerController* MouseCameraLock;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	void Jump();
	void Dash();

	void GrabCamera();
	void ReleaseCamera();
	void MoveForward(float Value);	
	void MoveRight(float Value);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	//void StartCameraShake(float Scale);

	UPROPERTY(EditDefaultsOnly)
	int16 JumpCount = 0;
	UPROPERTY(EditAnywhere)
	float BaseLookUpRate = 10.f;
	UPROPERTY(EditAnywhere)
	float BaseLookRightRate = 10.f;
	
	

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

};
