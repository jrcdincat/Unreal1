// Fill out your copyright notice in the Description page of Project Settings.


#include "Unreal1Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AUnreal1Player::AUnreal1Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateAbstractDefaultSubobject <UCameraComponent>("Camera");

	// Set the Root Component to be our Mesh.
	RootComponent = Mesh;
	// Attach the SpringArm to the Mesh, Spring will now follow the Mesh transform.
	SpringArm->SetupAttachment(Mesh);
	// Attach the Camera to the SpringArm, Camera will now follow the SpringArm transform.
	Camera->SetupAttachment(SpringArm);

	// Set Physics to True
	Mesh->SetSimulatePhysics(true);

	Mesh->OnComponentHit.AddDynamic(this, &AUnreal1Player::OnHit);
}

// Called when the game starts or when spawned
void AUnreal1Player::BeginPlay()
{
	Super::BeginPlay();
	// Account for mass in MoveForce and JumpImpulse
	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
}


// Called to bind functionality to input
void AUnreal1Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Custom Input Axis Bindings.
	InputComponent->BindAxis("MoveForward", this, &AUnreal1Player::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AUnreal1Player::MoveRight);
	// Custom Action Binding.
	InputComponent->BindAction("Jump", IE_Pressed, this, &AUnreal1Player::Jump);
}

void AUnreal1Player::MoveRight(float Value)
{
	// Get the Right vector of the camera as it doesn't rotate and move the player in this direction based on the input and MoveForce.
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void AUnreal1Player::MoveForward(float Value)
{
	// Get the Forward vector of the camera as it doesn't rotate and move the player in this direction based on the input and MoveForce.
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);
}

void AUnreal1Player::Jump()
{
	// Cap the number of jumps we can make.
	if (JumpCount >= MaxJumpCount) { return; }
	// Apply an impulse to the Mesh in the Z Axis.
	Mesh->AddImpulse(FVector(0, 0, JumpImpulse));
	// Track how many times we've jumped.
	JumpCount++;
}

void AUnreal1Player::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// Get Direction we hit the surface on the Z axis.
	const float HitDirection = Hit.Normal.Z;

	// If it's more than 0 then we've hit something below us. 1 is flat, anything between is a slope.
	if (HitDirection > 0)
	{
		JumpCount = 0;
	}
}
