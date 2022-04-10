// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ARollaBallPlayer::ARollaBallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	
	RootComponent = Sphere;
	Mesh->SetupAttachment(Sphere);
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ARollaBallPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARollaBallPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARollaBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollaBallPlayer::Jump);
	InputComponent->BindAction("Dash", IE_Pressed, this, &ARollaBallPlayer::Dash);

	InputComponent->BindAxis("MoveForward", this, &ARollaBallPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollaBallPlayer::MoveRight);

}

void ARollaBallPlayer::Jump()
{
	if(bCanJump)
	{
		const FVector Jump = Camera->GetUpVector() * JumpImpulse;
		Sphere->AddImpulse(Jump);
	}
	
	
}

void ARollaBallPlayer::Dash()
{
	const FVector Dash = Camera->GetForwardVector() * JumpImpulse;
	Sphere->AddImpulse(Dash);
}

void ARollaBallPlayer::MoveForward(float Value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Sphere->AddForce(Forward);
}

void ARollaBallPlayer::MoveRight(float Value)
{
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Sphere->AddForce(Right);
}