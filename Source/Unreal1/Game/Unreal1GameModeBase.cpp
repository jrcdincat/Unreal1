// Fill out your copyright notice in the Description page of Project Settings.


#include "Unreal1GameModeBase.h"
#include "Unreal1Widget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Unreal1/Items/Unreal1ItemBase.h"

void AUnreal1GameModeBase::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnreal1ItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();

	if (GameWidgetClass)
	{
		GameWidget = Cast<UUnreal1Widget>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void AUnreal1GameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void AUnreal1GameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}
