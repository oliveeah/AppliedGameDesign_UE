// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "MySpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class APPLIEDGAMEDESIGN_UE_API AMySpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	AMySpectatorPawn();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* sceneCamera;
};
