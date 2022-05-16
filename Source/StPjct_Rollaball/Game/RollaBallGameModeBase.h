// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollaBallGameModeBase.generated.h"

class URollaBallWidget;

UCLASS()
class STPJCT_ROLLABALL_API ARollaBallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	int32 ItemsCollected =0;
	int32 ItemsInLevel = 0;

	virtual void BeginPlay() override;
	void UpdateItemText();

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget>GameWigdetClass;

	UPROPERTY()
	URollaBallWidget* GameWidget;

public:

	void ItemCollected();

};
