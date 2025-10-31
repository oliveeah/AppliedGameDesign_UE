// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TouchGameMode.generated.h"

/**
 * 
 */
UCLASS()
class APPLIEDGAMEDESIGN_UE_API ATouchGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	void calculateRandomNumbers();

	void assignTextToSigns();

	int32 numberOfOdd = 0;
	int32 numberOfEven = 0;
	UPROPERTY(VisibleAnywhere)
	bool evenIsFull = false;

	UPROPERTY(VisibleAnywhere)

	bool oddIsFull = false;


public:
	
	ATouchGameMode();

	void setIsOddFull(bool _isOddFull);
	void setIsEvenFull(bool _isEvenFull);

	UFUNCTION(BlueprintCallable)
	bool checkIfLevelIsComplete();

	UFUNCTION(BlueprintCallable)
	bool checkIfOddIsFull();

	UFUNCTION(BlueprintCallable)
	bool checkIfEvenIsFull();

	UPROPERTY(VisibleAnywhere)

	bool levelIsComplete = false;

//	ACameraActor* cameraActor;
};
