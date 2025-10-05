// Fill out your copyright notice in the Description page of Project Settings.


#include "grabbableObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameplayTagContainer.h"

// Sets default values
AgrabbableObject::AgrabbableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	//SetRootComponent(root);
	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("box collider"));
	SetRootComponent(boxCollision);
	boxCollision->SetSimulatePhysics(true);

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(boxCollision);
	mesh->SetSimulatePhysics(false);

	FGameplayTag grabbableObjectTag = FGameplayTag::RequestGameplayTag(FName("canGrab"));


}



// Called when the game starts or when spawned
void AgrabbableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AgrabbableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

