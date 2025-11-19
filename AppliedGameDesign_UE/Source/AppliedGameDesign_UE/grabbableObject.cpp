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
#include "signs.h"

// Sets default values
AgrabbableObject::AgrabbableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	capsuleCollison = CreateDefaultSubobject<UCapsuleComponent>(TEXT("box collider"));
	SetRootComponent(capsuleCollison);
	capsuleCollison->SetSimulatePhysics(true);
	//capsuleCollison->SetLinearDamping(0.f);
	//capsuleCollison->SetAngularDamping(10.f);


	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	mesh->SetupAttachment(capsuleCollison);
	mesh->SetSimulatePhysics(false);


	textRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("textRender"));
	textRender->SetupAttachment(capsuleCollison);


	textRenderBackDrop = CreateDefaultSubobject<UTextRenderComponent>(TEXT("textRenderBackdrop"));
	textRenderBackDrop->SetupAttachment(capsuleCollison);

	floorBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FLOORBOX"));
	floorBox->SetupAttachment(capsuleCollison);

}



// Called when the game starts or when spawned
void AgrabbableObject::BeginPlay()
{
	Super::BeginPlay();
	
	capsuleCollison->OnComponentBeginOverlap.AddDynamic(this, &AgrabbableObject::OverlapBegin);
	capsuleCollison->OnComponentEndOverlap.AddDynamic(this, &AgrabbableObject::OverlapEnd);

	startLocation = GetActorLocation();
	startRotation = GetActorRotation();
}

// Called every frame
void AgrabbableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AgrabbableObject::setRandomNum(int32 randomNumGenerated)
{


	textRender->SetText(FText::AsNumber(randomNumGenerated));
	textRenderBackDrop->SetText(FText::AsNumber(randomNumGenerated));

}

void AgrabbableObject::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag("sign_box"))
		{
			UE_LOG(LogTemp, Warning, TEXT("collision"));

			Asigns* overlappingSign = Cast<Asigns>(OtherActor);
			if (overlappingSign)
			{
				bool isOverlappingSign_Odd = overlappingSign->getIsOdd();
				if (isOverlappingSign_Odd == grabbableIsOdd)
				{
					overlappingSign->newCollision(grabbableIsOdd, true);
				}
			}
			
		}
		else if (OtherActor->ActorHasTag("outerBounds"))
		{
			SetActorLocationAndRotation(startLocation, startRotation, /*bSweep=*/false, /*OutSweep=*/nullptr, ETeleportType::ResetPhysics);
			capsuleCollison->SetPhysicsLinearVelocity(FVector::ZeroVector);
		}
	}
}


void AgrabbableObject::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag("sign_box"))
		{

			UE_LOG(LogTemp, Warning, TEXT("collision"));

			Asigns* overlappingSign = Cast<Asigns>(OtherActor);
			if (overlappingSign)
			{
				bool isOverlappingSign_Odd = overlappingSign->getIsOdd();
				if (isOverlappingSign_Odd == grabbableIsOdd)
				{
					overlappingSign->removedCollision(grabbableIsOdd, false);
				}
			}

		}
	}
}


void AgrabbableObject::getIsFlyingCallback()
{
	onMyEvent.Broadcast(isFlying);
}


void AgrabbableObject::playSFXCallback()
{
	if (uniqueCry)
	{
		playSFX_Event.Broadcast(uniqueCry);

	}
}

void AgrabbableObject::set_grabbableIsOdd(bool _isOdd)
{
	grabbableIsOdd = _isOdd;
}

bool AgrabbableObject::get_grabbableIsOdd()
{
	return grabbableIsOdd;
}

void AgrabbableObject::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

		if (Other && Other->ActorHasTag("floor"))
		{	

			if (!groundedDoOnce) { //if not grounded
				groundedDoOnce = true; //grounded now true, do once
				
				//isFlying = false;


				if(isFlying){
					setIsFlying(false);
				}

			}
		}
	
		//GetWorldTimerManager().ClearTimer(groundedTimerHandle);
		GetWorldTimerManager().SetTimer(groundedTimerHandle, this, &AgrabbableObject::clearTimer, 0.35f, false);
}

void AgrabbableObject::clearTimer()
{
	

	//UE_LOG(LogTemp, Warning, TEXT("reset grounded doonce"));
	groundedDoOnce = false;
	//UE_LOG(LogTemp, Warning, TEXT("///////////////////////////////////////////////////"));




}



void AgrabbableObject::setIsFlying(bool _isFlying)
{
	isFlying = _isFlying;

	if (isFlying)
	{
		UE_LOG(LogTemp, Display, TEXT("is flying "));
		getIsFlyingCallback();
		playSFXCallback();

	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("not flying"));
		getIsFlyingCallback();
	}
}






