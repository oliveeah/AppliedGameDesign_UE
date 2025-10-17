// Fill out your copyright notice in the Description page of Project Settings.


#include "signs.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "grabbableObject.h"

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

	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("boxCollision"));
	boxCollider->SetupAttachment(sceneRoot);

}

// Called when the game starts or when spawned
void Asigns::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Asigns::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Asigns::setText(FText text)
{
	textRender->SetText(text);
}

void Asigns::setIsOdd(bool _isOdd)
{
	isOdd = _isOdd;
}

bool Asigns::checkIfBoxHasAllGrabbables()
{
	return false;
}

