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

}

// Called to bind functionality to input
void AplayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(interactAction, ETriggerEvent::Started, this, &AplayerPawn::interactCallback);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("no enhanced input detected"));

	}
}

void AplayerPawn::interactCallback()
{
	UE_LOG(LogTemp, Warning, TEXT("input callback called"));
	
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();//get player controller and check ptr
	if (!playerController) { return; }

	FHitResult hit;

	bool hasHit = playerController->GetHitResultUnderCursor(ECC_Visibility, false, hit);//gets hit under cursor

	if(hasHit)//if true
	{
		DrawDebugSphere(GetWorld(), hit.ImpactPoint, 10.0f, 12, FColor::Red, false, 2.0f);//draw debug sphere

		if (hit.GetActor() && hit.GetActor()->ActorHasTag("canGrab"))//if hit actor has tag
		{
			UE_LOG(LogTemp, Display, TEXT("grabbable object grabbed"));
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("object cannot be grabbed"));
		}
	}
}







