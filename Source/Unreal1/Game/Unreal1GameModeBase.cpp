// Fill out your copyright notice in the Description page of Project Settings.


#include "Unreal1GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Unreal1/Items/Unreal1ItemBase.h"

void AUnreal1GameModeBase::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnreal1ItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();
}

void AUnreal1GameModeBase::UpdateItemText()
{
}

void AUnreal1GameModeBase::ItemCollected()
{
	ItemsCollected++;
}
