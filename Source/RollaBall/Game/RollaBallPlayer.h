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
	
	ARollaBallPlayer();	

protected:
	
	virtual void BeginPlay() override;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	
	void Charge();
	void Release();
	void Jump();
	void AirSlam();
	void ResetPosition();
	void MoveForward(float Value);	
	void MoveRight(float Value);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);

	UPROPERTY(EditDefaultsOnly)
	float MoveForce = 500.f;
	UPROPERTY(EditDefaultsOnly)
	float JumpImpulse = 500.f;
	UPROPERTY(EditDefaultsOnly)
	float SlamImpulse = 300.f;
	UPROPERTY(EditDefaultsOnly)
	float CameraLookRate = 20.f;
	UPROPERTY(EditDefaultsOnly)
	float SuperchargeMultiplier = 2.f;	
	
	float Supercharge = 0;	
	float MaxSupercharge = 2.f;
	float SlamForceMultiplier = 5.f;	
	int MaxDashCount = 1;	
	int DashCount = 0;	
	bool bCharging = false;	
	bool bSlammed = false;
	bool bGrounded = true;

	FVector PlayerSpawnLocation{};

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
	
public:
	float GetCurrentSupercharge() const { return Supercharge;}
	float GetMaxCharge() const { return MaxSupercharge;}		
};
