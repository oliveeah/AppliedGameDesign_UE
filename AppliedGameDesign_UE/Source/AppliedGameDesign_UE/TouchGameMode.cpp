// Fill out your copyright notice in the Description page of Project Settings.


#include "TouchGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "grabbableObject.h"



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

void ATouchGameMode::BeginPlay()
{
	Super::BeginPlay();

	calculateRandomNumbers();


	//while (i <= 4)
	//{
	//	int32 randomNum = FMath::RandRange(0, 100);
	//	for (int32 randomNum : intArray)
	//	{
	//		if(randomNum)
	//	}
	//}
}

void ATouchGameMode::calculateRandomNumbers()
{
	TArray<AActor*> FoundObjects;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AgrabbableObject::StaticClass(), FoundObjects);

	UE_LOG(LogTemp, Display, TEXT(" number of found objects: %d"), FoundObjects.Num());

	int32 numOfGrabbableObjectsInScene = FoundObjects.Num();

	TSet<int32> randomNumberTSet;

	int32 i = numOfGrabbableObjectsInScene;
	while (i != 0)
	{
		int32 randomNum = FMath::RandRange(0, 100);
		if (!randomNumberTSet.Contains(randomNum))
		{
			randomNumberTSet.Add(randomNum);
			i--;
		}
	}
	TArray<int32> randomNumberArray = randomNumberTSet.Array();


	int l = 0;
	for (AActor* Actor : FoundObjects)
	{
		if (AgrabbableObject* Grabbable = Cast<AgrabbableObject>(Actor))
		{
			Grabbable->setRandomNum(randomNumberArray[l]); // Example function in your class
		}
		l++;
	}

}
