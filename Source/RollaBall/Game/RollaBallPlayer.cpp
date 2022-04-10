// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ARollaBallPlayer::ARollaBallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	
	RootComponent = Mesh;	
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);
	
	Mesh->SetSimulatePhysics(true);

	Mesh->OnComponentHit.AddDynamic(this, &ARollaBallPlayer::OnHit);
}

// Called when the game starts or when spawned
void ARollaBallPlayer::BeginPlay()
{
	Super::BeginPlay();

	JumpImpulse *= Mesh->GetMass();
	MoveForce *= Mesh->GetMass();	
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
	if(JumpCount < MaxJumpCount)
	{
		const FVector Jump = Camera->GetUpVector() * JumpImpulse;
		Mesh->AddImpulse(Jump);
		JumpCount++;		
	}	
}

void ARollaBallPlayer::Dash()
{
	const FVector Dash = Camera->GetForwardVector() * JumpImpulse;
	Mesh->AddImpulse(Dash);
}

void ARollaBallPlayer::MoveForward(float Value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);
}

void ARollaBallPlayer::MoveRight(float Value)
{
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollaBallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const float HitDirection = Hit.Normal.Z;	
	
	if(HitDirection > 0)	
		JumpCount = 0;
		
	
		
}
