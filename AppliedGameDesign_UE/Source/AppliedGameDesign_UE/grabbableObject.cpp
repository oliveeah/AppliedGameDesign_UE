// Fill out your copyright notice in the Description page of Project Settings.


#include "grabbableObject.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameplayTagContainer.h"
#include "Components/TextRenderComponent.h"
#include "PhysicsEngine/BodyInstance.h"


// Sets default values
AgrabbableObject::AgrabbableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	//SetRootComponent(root);
	capsuleCollison = CreateDefaultSubobject<UCapsuleComponent>(TEXT("box collider"));
	SetRootComponent(capsuleCollison);
	capsuleCollison->SetSimulatePhysics(true);
	capsuleCollison->SetLinearDamping(4.f);
	capsuleCollison->SetAngularDamping(10.f);
//	capsuleCollison->BodyInstance.bNotifyRigidBodyCollision = true;


	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	mesh->SetupAttachment(capsuleCollison);
	mesh->SetSimulatePhysics(false);

	//FGameplayTag grabbableObjectTag = FGameplayTag::RequestGameplayTag(FName("canGrab"));

	textRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("textRender"));
	textRender->SetupAttachment(capsuleCollison);


}



// Called when the game starts or when spawned
void AgrabbableObject::BeginPlay()
{
	Super::BeginPlay();
	
	//int32 randomNum = FMath::RandRange(0, 100);

	
	//UE_LOG(LogTemp, Display, TEXT("Random Number: %d"), randomNum);

	//capsuleCollison->OnComponentSleep.AddDynamic(this, &AgrabbableObject::OnSleep);
	//capsuleCollison->OnComponentWake.AddDynamic(this, &AgrabbableObject::OnWake);


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

void AgrabbableObject::setIsFlying(bool _isFlying)
{
	//if (isFlying == _isFlying) return;
//isFlying = !isFlying;

	if (_isFlying)
	{
		UE_LOG(LogTemp, Warning, TEXT("isflying"));
	}
	else
	{
		SetActorTickEnabled(false);

		UE_LOG(LogTemp, Warning, TEXT("notflying"));

	}
}

//void AgrabbableObject::OnSleep(UPrimitiveComponent* SleepingComponent, FName BoneName)
//{
//	setIsFlying(false);
//}
//
//void AgrabbableObject::OnWake(UPrimitiveComponent* WakingComponent, FName BoneName)
//{
//	setIsFlying(true);
//
//}




