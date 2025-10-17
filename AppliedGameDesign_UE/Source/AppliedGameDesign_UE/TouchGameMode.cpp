// Fill out your copyright notice in the Description page of Project Settings.


#include "TouchGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "grabbableObject.h"
#include "signs.h"


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
	assignTextToSigns();


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
		int32 randomNum = FMath::RandRange(1, 100);
		if (!randomNumberTSet.Contains(randomNum))
		{
			randomNumberTSet.Add(randomNum);
			if (randomNum % 2 == 0)
			{
				numberOfEven++;
			}
			else
			{
				numberOfOdd++;
			}
			i--;
		}
	}
	TArray<int32> randomNumberArray = randomNumberTSet.Array();


	int l = 0;
	for (AActor* Actor : FoundObjects)
	{
		if (AgrabbableObject* Grabbable = Cast<AgrabbableObject>(Actor))
		{
			Grabbable->setRandomNum(randomNumberArray[l]); 
		}
		l++;
	}
	if (GEngine)//debug
	{
		GEngine->AddOnScreenDebugMessage(
			-1,                
			5.0f,              
			FColor::Green,     
			FString::Printf(TEXT("numberOfOdd = %d"), numberOfOdd) 
		);		

		GEngine->AddOnScreenDebugMessage(
			-1,
			5.0f,
			FColor::Green,
			FString::Printf(TEXT("numberOfEven = %d"), numberOfEven)
		);


	}
}

void ATouchGameMode::assignTextToSigns()
{

	FMath::RandInit(FDateTime::Now().GetMillisecond());//random seed generator

	TArray<AActor*> FoundSigns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asigns::StaticClass(), FoundSigns);//get all signs put them in array

	if (FoundSigns.Num() < 2)
	{
				return;//if not enough signs return
	}

	// Shuffle signs randomly
	for (int32 i = 0; i < FoundSigns.Num(); i++)
	{
		int32 SwapIndex = FMath::RandRange(0, FoundSigns.Num() - 1);
		FoundSigns.Swap(i, SwapIndex);
	}

	bool _randBool = FMath::RandBool();//random value of 1 or 0

	if (Asigns* Sign1 = Cast<Asigns>(FoundSigns[0]))//pointer check and declaration
	{
		Sign1->setText(FText::FromString(_randBool ? "odd" : "even")); //condititonal if
		Sign1->setIsOdd(_randBool ? 1 : 0);
	}

	if (Asigns* Sign2 = Cast<Asigns>(FoundSigns[1]))//pointer check and declaration
	{
		Sign2->setText(FText::FromString(_randBool ? "even" : "odd")); //condititonal if
		Sign2->setIsOdd(_randBool ? 0 : 1);
	}



}
