// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "signs.generated.h"

UCLASS()
class APPLIEDGAMEDESIGN_UE_API Asigns : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Asigns();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* sceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Math")
	class UTextRenderComponent* textRender;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Math")
	class UBoxComponent* boxCollider;

	UFUNCTION()
	 void signs_OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	 void signs_OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void setText(FText text);

	virtual void setIsOdd(bool _isOdd);

	virtual bool checkIfBoxHasAllGrabbables();

	UPROPERTY(VisibleAnywhere)
	bool isOdd;


	UPROPERTY(VisibleAnywhere)
	int numberOfOverlappedActors;

	UPROPERTY(VisibleAnywhere)
	int numberOfActorsInSceneNeeded;

	virtual void setNumberOfActorsNeeded(int numberNeeded);
};
