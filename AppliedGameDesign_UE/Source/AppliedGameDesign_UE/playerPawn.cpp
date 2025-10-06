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


	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (defaultMappingContext)
				{
					Subsystem->AddMappingContext(defaultMappingContext, 0);
					UE_LOG(LogTemp, Warning, TEXT("Mapping context added."));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("No mapping context assigned!"));
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

		APlayerController* playerController = GetWorld()->GetFirstPlayerController();//get player controller and check ptr
		if (!playerController) { return; }

		playerController->GetMousePosition(mouseX, mouseY);

		FVector worldLocation, worldDirection;

		playerController->DeprojectScreenPositionToWorld(mouseX, mouseY, worldLocation, worldDirection);

		float Distance = 400.f;
		FVector TargetLocation = worldLocation + (worldDirection * Distance);

		physicsHandle->SetTargetLocationAndRotation(
			TargetLocation,
			playerController->PlayerCameraManager->GetCameraRotation()
		);
	}
	else
	{
		physicsHandle->ReleaseComponent();
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
		UE_LOG(LogTemp, Warning, TEXT("no enhanced input detected"));

	}
}

void AplayerPawn::interactCallbackHolding()
{
	UE_LOG(LogTemp, Warning, TEXT("input callback called"));
	
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();//get player controller and check ptr
	if (!playerController) { return; }

	FHitResult hit;

	bool hasHit = playerController->GetHitResultUnderCursor(ECC_Visibility, false, hit);//gets hit under cursor

	if(hasHit)//if true
	{
		DrawDebugSphere(GetWorld(), hit.ImpactPoint, 10.0f, 12, FColor::Red, false, 2.0f);//draw debug sphere

		if (AActor* hitActor = hit.GetActor())
		{
			if (hitActor->IsA(AgrabbableObject::StaticClass()))
			{
				UE_LOG(LogTemp, Display, TEXT("grabbableObject actor hit"));

				if (!physicsHandle) { return; }

				UPrimitiveComponent* hitComponent = hit.GetComponent();
				physicsHandle->GrabComponentAtLocationWithRotation(
					hitComponent,
					NAME_None,
					hitComponent->GetComponentLocation(),
					hitComponent->GetComponentRotation()
				);
				isHolding = true;
			}
		}


	}
}

void AplayerPawn::interactCallbackRelease()
{
	isHolding = false;
}







