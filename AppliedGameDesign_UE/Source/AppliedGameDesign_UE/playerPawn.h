// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Logging/LogMacros.h"
#include "playerPawn.generated.h"



class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;


UCLASS()
class APPLIEDGAMEDESIGN_UE_API AplayerPawn : public APawn
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* springArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* camera;

public:
	// Sets default values for this pawn's properties
	AplayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* root;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* mesh;



protected:

	// Input mapping context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* defaultMappingContext;

	//interact action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* interactAction;
public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void interactCallbackHolding();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void interactCallbackRelease();

	bool isHolding = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UPhysicsHandleComponent* physicsHandle;

	APlayerController* playerController;
};
