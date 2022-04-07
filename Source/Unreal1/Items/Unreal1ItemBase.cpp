// Fill out your copyright notice in the Description page of Project Settings.


#include "Unreal1ItemBase.h"
#include "Unreal1/Game//Unreal1Player.h"

// Sets default values
AUnreal1ItemBase::AUnreal1ItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AUnreal1ItemBase::OverlapBegin);
}

// Called when the game starts or when spawned
void AUnreal1ItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUnreal1ItemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AUnreal1Player>(OtherActor) != nullptr)
	{
		Collected();
	}
}

void AUnreal1ItemBase::Collected_Implementation()
{
	// TODO - Do Game Mode Stuff
}

