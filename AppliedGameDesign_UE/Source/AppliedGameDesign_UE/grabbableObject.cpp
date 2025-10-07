// Fill out your copyright notice in the Description page of Project Settings.


#include "grabbableObject.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameplayTagContainer.h"
#include "Components/TextRenderComponent.h"


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
	boxCollision->SetLinearDamping(4.f);
	boxCollision->SetAngularDamping(10.f);

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	mesh->SetupAttachment(boxCollision);
	mesh->SetSimulatePhysics(false);

	//FGameplayTag grabbableObjectTag = FGameplayTag::RequestGameplayTag(FName("canGrab"));

	textRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("textRender"));
	textRender->SetupAttachment(boxCollision);


}



// Called when the game starts or when spawned
void AgrabbableObject::BeginPlay()
{
	Super::BeginPlay();
	
	//int32 randomNum = FMath::RandRange(0, 100);

	
	//UE_LOG(LogTemp, Display, TEXT("Random Number: %d"), randomNum);

}

// Called every frame
void AgrabbableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AgrabbableObject::setRandomNum(int32 randomNumGenerated)
{


	textRender->SetText(FText::AsNumber(randomNumGenerated));

}

