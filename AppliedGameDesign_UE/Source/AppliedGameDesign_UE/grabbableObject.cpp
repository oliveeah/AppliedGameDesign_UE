// Fill out your copyright notice in the Description page of Project Settings.


#include "grabbableObject.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameplayTagContainer.h"
#include "Components/TextRenderComponent.h"
#include "PhysicsEngine/BodyInstance.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"

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

	floorBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FLOORBOX"));
	floorBox->SetupAttachment(capsuleCollison);


}



// Called when the game starts or when spawned
void AgrabbableObject::BeginPlay()
{
	Super::BeginPlay();
	
	floorBox->OnComponentBeginOverlap.AddDynamic(this, &AgrabbableObject::OverlapBegin);
	floorBox->OnComponentEndOverlap.AddDynamic(this, &AgrabbableObject::OverlapEnd);


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

void AgrabbableObject::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag(FName("floor")))
		{
			UE_LOG(LogTemp, Display, TEXT("grounded"));
			isFlying = false;
			stopAnimation();
		}
	}
}

void AgrabbableObject::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag(FName("floor")))
		{
			UE_LOG(LogTemp, Display, TEXT("in air"));
			isFlying = true;
			playAnimation();

		}
	}
}

bool AgrabbableObject::playAnimation()
{
	return isFlying;
}

void AgrabbableObject::stopAnimation()
{

}









