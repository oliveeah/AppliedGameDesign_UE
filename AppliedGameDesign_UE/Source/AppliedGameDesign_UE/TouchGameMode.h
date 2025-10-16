// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TouchGameMode.generated.h"

/**
 * 
 */
UCLASS()
class APPLIEDGAMEDESIGN_UE_API ATouchGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	void calculateRandomNumbers();

	void assignTextToSigns();

public:
	
	ATouchGameMode();

//	ACameraActor* cameraActor;
};
