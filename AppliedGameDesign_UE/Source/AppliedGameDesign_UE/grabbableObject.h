// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "grabbableObject.generated.h"


UCLASS()
class APPLIEDGAMEDESIGN_UE_API AgrabbableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AgrabbableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* root;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision", meta =(AllowPrivateAccess = "true"))
	class UBoxComponent* boxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Math")
	class UTextRenderComponent* textRender;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void setRandomNum(int32 randomNumGenerated);

};
