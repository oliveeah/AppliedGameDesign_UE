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
	
}

// Called every frame
void AplayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AplayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(interactAction, ETriggerEvent::Triggered, this, &AplayerPawn::interactCallback);
		UE_LOG(LogTemp, Warning, TEXT("enhanced input detected"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("no enhanced input detected"));

	}
}

void AplayerPawn::interactCallback()
{
	UE_LOG(LogTemp, Warning, TEXT("input callback called"));

}



