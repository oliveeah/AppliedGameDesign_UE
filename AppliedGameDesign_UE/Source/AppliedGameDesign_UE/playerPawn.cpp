// Fill out your copyright notice in the Description page of Project Settings.
#include "playerPawn.h" 

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "grabbableObject.h"

// Sets default values
AplayerPawn::AplayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		
		root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
		SetRootComponent(root);
	
		mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		mesh->SetupAttachment(root);

		springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
		springArm->SetupAttachment(root);
		springArm->TargetArmLength = 400.0f;
		springArm->bUsePawnControlRotation = true;

		camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
		camera->SetupAttachment(springArm, USpringArmComponent::SocketName);
		camera->bUsePawnControlRotation = false;

		physicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

		//physicsHandle->SetupAttachment(root);

}

// Called when the game starts or when spawned
void AplayerPawn::BeginPlay()
{
	Super::BeginPlay();
	playerController = Cast<APlayerController>(GetController());
	if (!playerController)
	{
		playerController = GetWorld()->GetFirstPlayerController();
	}

	if (playerController)
	{
		if (ULocalPlayer* LocalPlayer = playerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (defaultMappingContext)
				{
					Subsystem->AddMappingContext(defaultMappingContext, 0);
				}
				else
				{
				}
			}
		}
	}
}

// Called every frame
void AplayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isHolding && physicsHandle && physicsHandle->GrabbedComponent)
	{
		float mouseX, mouseY;


		playerController->GetMousePosition(mouseX, mouseY);

		FVector worldLocation, worldDirection;

		playerController->DeprojectScreenPositionToWorld(mouseX, mouseY, worldLocation, worldDirection);


		FPlane GrabPlane(FVector(0, 0, grabbedHeight), FVector::UpVector);

		FVector TargetLocation;
		if (FMath::SegmentPlaneIntersection(worldLocation, worldLocation + worldDirection * 10000.f, GrabPlane, TargetLocation))
		{
			const float LiftOffset = 150.0f;  // Raise 150 units upwards
			TargetLocation.Z += LiftOffset;


			physicsHandle->SetTargetLocationAndRotation(
				TargetLocation,
				playerController->PlayerCameraManager->GetCameraRotation()
			);
		}
	}

}

// Called to bind functionality to input
void AplayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(interactAction, ETriggerEvent::Started, this, &AplayerPawn::interactCallbackHolding);
		EnhancedInputComponent->BindAction(interactAction, ETriggerEvent::Completed, this, &AplayerPawn::interactCallbackRelease);

	}
	else
	{

	}
}

void AplayerPawn::interactCallbackHolding()
{
	SetActorTickEnabled(true);


	
	//get player controller and check ptr
	if (!playerController) { return; }

	FHitResult hit;

	bool hasHit = playerController->GetHitResultUnderCursor(ECC_Visibility, false, hit);//gets hit under cursor

	if(hasHit)//if true
	{

		if (AActor* hitActor = hit.GetActor())
		{
			if (hitActor->IsA(AgrabbableObject::StaticClass()))//if hit an actor and its grabbable
			{

				if (!physicsHandle) { return; }

				UPrimitiveComponent* hitComponent = hit.GetComponent();

				if (!hitComponent || !hitComponent->IsSimulatingPhysics()) { return; } //ptr checks

				physicsHandle->GrabComponentAtLocationWithRotation(
					hitComponent,
					NAME_None,
					hitComponent->GetComponentLocation(),
					hitComponent->GetComponentRotation()
				);

				grabbedHeight = hitComponent->GetComponentLocation().Z;

				isHolding = true;

				currentlyGrabbedObject = Cast<AgrabbableObject>(hitActor);
				if (currentlyGrabbedObject)
				{
					currentlyGrabbedObject->setIsFlying(true);					
					currentlyGrabbedObject->SetActorEnableCollision(false);

				}

		
			
			}
		}


	}
}

void AplayerPawn::interactCallbackRelease()
{
	SetActorTickEnabled(false);


	isHolding = false;
	if (physicsHandle && physicsHandle->GrabbedComponent)
	{
		physicsHandle->ReleaseComponent();
	}

	if (currentlyGrabbedObject)
	{
		//currentlyGrabbedObject->setIsFlying(false);
		currentlyGrabbedObject->SetActorEnableCollision(true);

		currentlyGrabbedObject = nullptr;

	}




}







