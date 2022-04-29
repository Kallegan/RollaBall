// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "RollaBall/Game/RollaBallGameModeBase.h"
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
	
	//added a multiplier to reduce the total needed to see an effect when tuning stuff.
	JumpImpulse *= 75.f;
	MoveForce *=75.f;
	SlamImpulse *= 75.f;
	PlayerSpawnLocation = GetController()->GetPawn()->GetActorLocation();
}

// Called every frame
void ARollaBallPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	
	if(bCharging && Supercharge < MaxSupercharge && DashCount < MaxDashCount)
	Supercharge+=DeltaTime;	
}

void ARollaBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);	
	
	InputComponent->BindAction("SuperCharge", IE_Pressed, this, &ARollaBallPlayer::Charge);
	InputComponent->BindAction("SuperCharge", IE_Released, this, &ARollaBallPlayer::Release);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollaBallPlayer::Jump);
	InputComponent->BindAction("Slam", IE_Pressed, this, &ARollaBallPlayer::AirSlam);
	
	InputComponent->BindAction("Restart", IE_Pressed, this, &ARollaBallPlayer::ResetPosition);
	
	InputComponent->BindAxis("MoveForward", this, &ARollaBallPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollaBallPlayer::MoveRight);

	InputComponent->BindAxis("LookUp", this, &ARollaBallPlayer::LookUp);
	InputComponent->BindAxis("LookRight", this, &ARollaBallPlayer::LookRight);	
}

void ARollaBallPlayer::Charge()
{	
	bCharging = true;
	ChargeStarted();	
}

void ARollaBallPlayer::Release()
{
	ChargeEnded();
	bCharging = false;
	if(Supercharge > 0.2f)
	{
		const float DashMultiplier = JumpImpulse * (1+ Supercharge/2 * SuperchargeMultiplier);
		
		const FVector Dash = Camera->GetForwardVector().GetSafeNormal2D() * DashMultiplier;		
		
		Mesh->AddImpulse(Dash);		
		Supercharge = 0.f;
		
		if(DashCount < MaxDashCount)
		{		
			DashCount++;
			bGrounded = false;
		}
	}
	else	
		Supercharge = 0;
	
}

void ARollaBallPlayer::Jump()
{		
	if(Supercharge != 0)
	{
		const float ChargeForce = JumpImpulse * (1+Supercharge/2);
		const FVector Jump = GetActorLocation().UpVector * ChargeForce;
	
		Mesh->AddImpulse(Jump);				
	}
	else if(DashCount < MaxDashCount)
	{
		const FVector Jump = GetActorLocation().UpVector * JumpImpulse;
		Mesh->AddImpulse(Jump);				
	}
	else
		return;
	
	DashCount++;
	bGrounded = false;
	Supercharge = 0.f;	
}

void ARollaBallPlayer::AirSlam()
{
	if(!bSlammed)
	{
		Mesh->SetSimulatePhysics(false);		
		const FVector Slam = GetActorLocation().DownVector * SlamImpulse * SlamForceMultiplier;
		Mesh->SetSimulatePhysics(true);
		Mesh->AddImpulse(Slam);
		bSlammed = true;

		UE_LOG(LogTemp, Warning, TEXT("SLAM"))
	}
	SlamStarted();
	Supercharge = 0;
}

void ARollaBallPlayer::ResetPosition()
{
	Mesh->SetSimulatePhysics(false);	
	GetController()->GetPawn()->SetActorLocation(PlayerSpawnLocation);		

	if(ARollaBallGameModeBase* GameMode = Cast<ARollaBallGameModeBase>(GetWorld()->GetAuthGameMode()))
			GameMode->PlayerResetPosition();

	ResettingPosition();
	CurrentLives--;

	if(CurrentLives <= 0)
		Destroy();
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
	if(!bGrounded)
	{
		const float HitDirection = Hit.Normal.Z;
		
		if(HitDirection > 0)
		{
			DashCount = 0;
			bGrounded = true;			
		}		
	}
	if(bSlammed == true)
	bSlammed = false;	
}

void ARollaBallPlayer::ResettingPosition_Implementation()
{
	Mesh->SetSimulatePhysics(true);
}

