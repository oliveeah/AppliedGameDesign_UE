// Fill out your copyright notice in the Description page of Project Settings.


#include "TouchGameMode.h"
#include "UObject/ConstructorHelpers.h"

ATouchGameMode::ATouchGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> defaultPawn(TEXT("/Game/blueprints/playerActor.playerActor"));
	DefaultPawnClass = defaultPawn.Class;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Gamemode is constructing"));
	}
}
