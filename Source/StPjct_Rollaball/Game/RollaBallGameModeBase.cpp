// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "StPjct_Rollaball/Items/RollaBallItemBase.h"
#include "RollaBallWidget.h"
#include "Blueprint/UserWidget.h"

void ARollaBallGameModeBase::BeginPlay()
{
	TArray <AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollaBallItemBase::StaticClass(), Items);

	//array size is the number of items in the level
	ItemsInLevel = Items.Num();

	//Making sure we take the custom widget
	if (GameWigdetClass)
	{
		GameWidget = Cast<URollaBallWidget>(CreateWidget(GetWorld(), GameWigdetClass));

		if (GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ARollaBallGameModeBase::UpdateItemText()
{

	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);

}

void ARollaBallGameModeBase::ItemCollected()
{
	ItemsCollected ++;
	UpdateItemText();
}
