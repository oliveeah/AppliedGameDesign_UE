// Fill out your copyright notice in the Description page of Project Settings.


#include "TouchGameMode.h"
#include "UObject/ConstructorHelpers.h"

ATouchGameMode::ATouchGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> defaultPawn(TEXT("/Game/blueprints/playerPawn_BP.playerPawn_BP"));
	DefaultPawnClass = defaultPawn.Class;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Gamemode is constructing"));
	}

	//ConstructorHelpers::FClassFinder<ASpectatorPawn> defaultCamera(TEXT("/Game/blueprints/MySpectatorPawn_BP.MySpectatorPawn_BP"));
		//SpectatorClass = defaultCamera.Class;
}
