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
	
	if(bCharging && Supercharge < MaxSupercharge)
	Supercharge+=DeltaTime;		
}

void ARollaBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);	
		
	InputComponent->BindAction("SuperCharge", IE_Pressed, this, &ARollaBallPlayer::Charge);
	InputComponent->BindAction("SuperCharge", IE_Released, this, &ARollaBallPlayer::Release);
	
	InputComponent->BindAxis("MoveForward", this, &ARollaBallPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollaBallPlayer::MoveRight);

	InputComponent->BindAxis("LookUp", this, &ARollaBallPlayer::LookUp);
	InputComponent->BindAxis("LookRight", this, &ARollaBallPlayer::LookRight);	
}

void ARollaBallPlayer::Charge()
{
	bCharging = true;	
}

void ARollaBallPlayer::Release()
{
	bCharging = false;
	if(Supercharge > 0.2f)
	{
		const float DashMultiplier = JumpImpulse * (1+ Supercharge * SuperchargeMultiplier);
		const FVector Dash = Camera->GetForwardVector() * FMath::Clamp(DashMultiplier, JumpImpulse, 250000.f);
	
		Mesh->AddImpulse(Dash);		
		Supercharge = 0.f;	
		if(DashCount < MaxDashCount)
		{		
			DashCount++;
			bGrounded = false;
		}
	}
	else
	{
		Supercharge = 0;
	}
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

void ARollaBallPlayer::LookUp(float AxisValue)
{	
	AddControllerPitchInput(AxisValue * CameraLookRate * GetWorld()->GetDeltaSeconds());
}


void ARollaBallPlayer::LookRight(float AxisValue)
{	
	AddControllerYawInput(AxisValue * CameraLookRate * GetWorld()->GetDeltaSeconds());
}


void ARollaBallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const float HitDirection = Hit.Normal.Z;	
	
	if(HitDirection > 0 && !bGrounded && DashCount != 0)
	{
		DashCount = 0;
		bGrounded = true;
	}		
}


