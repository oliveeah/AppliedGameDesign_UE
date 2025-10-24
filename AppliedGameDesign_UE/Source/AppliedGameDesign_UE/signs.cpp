// Fill out your copyright notice in the Description page of Project Settings.


#include "signs.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "grabbableObject.h"
#include "TouchGameMode.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
Asigns::Asigns()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("rootComponent"));
	SetRootComponent(sceneRoot);

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	staticMesh->SetupAttachment(sceneRoot);

	textRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("textRender"));
	textRender->SetupAttachment(sceneRoot);

	textRenderBackDrop = CreateDefaultSubobject<UTextRenderComponent>(TEXT("textRenderBackDrop"));
	textRenderBackDrop->SetupAttachment(sceneRoot);

	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("boxCollision"));
	boxCollider->SetupAttachment(sceneRoot);

}

// Called when the game starts or when spawned
void Asigns::BeginPlay()
{
	Super::BeginPlay();
	
	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &Asigns::signs_OverlapBegin);
	boxCollider->OnComponentEndOverlap.AddDynamic(this, &Asigns::signs_OverlapEnd);
}

void Asigns::signs_OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->GetClass()->IsChildOf(AgrabbableObject::StaticClass()))
	{
		//UE_LOG(LogTemp, Display, TEXT("is child"));
		AgrabbableObject* grabbable = Cast<AgrabbableObject>(OtherActor);
		
		bool grabbableIsOdd = grabbable->get_grabbableIsOdd();

		if (grabbable)
		{	
			if (isOdd && grabbableIsOdd || !isOdd && !grabbableIsOdd)
			{
				numberOfOverlappedActors++;


			}
		
		}
	}
	if (numberOfOverlappedActors == numberOfActorsInSceneNeeded)
	{

		ATouchGameMode* gameMode = Cast<ATouchGameMode>(UGameplayStatics::GetGameMode(this));
		if (gameMode)
		{
			if (isOdd)
			{
				UE_LOG(LogTemp, Display, TEXT("odd requirement met"));

				gameMode->setIsOddFull(true);
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("even requirement met"));

				gameMode->setIsEvenFull(true);

			}
		}
	}


}

void Asigns::signs_OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{


	if (OtherActor->GetClass()->IsChildOf(AgrabbableObject::StaticClass()))
	{
		AgrabbableObject* grabbable = Cast<AgrabbableObject>(OtherActor);

		bool grabbableIsOdd = grabbable->get_grabbableIsOdd();

		if (grabbable)
		{
			if (isOdd && grabbableIsOdd || !isOdd && !grabbableIsOdd)
			{
				numberOfOverlappedActors--;
			}

		}
	}
	if (numberOfOverlappedActors != numberOfActorsInSceneNeeded)
	{
		ATouchGameMode* gameMode = Cast<ATouchGameMode>(UGameplayStatics::GetGameMode(this));
		if (gameMode)
		{
			if (isOdd)
			{
				gameMode->setIsOddFull(false);
				UE_LOG(LogTemp, Display, TEXT("odd requirement NOT met"));

			}
			else
			{
				gameMode->setIsEvenFull(false);
				UE_LOG(LogTemp, Display, TEXT("even requirement NOT met"));

			}
		}
	}
}

// Called every frame
void Asigns::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Asigns::setText(FText text)
{
	textRender->SetText(text);
	textRenderBackDrop->SetText(text);
}

void Asigns::setIsOdd(bool _isOdd)
{
	isOdd = _isOdd;
}

bool Asigns::checkIfBoxHasAllGrabbables()
{
	return false;
}

void Asigns::setNumberOfActorsNeeded(int numberNeeded)
{
	numberOfActorsInSceneNeeded = numberNeeded;
}

