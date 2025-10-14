// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "GameFramework/Actor.h"
#include "grabbableObject.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIsFlyingChangedDelegate, bool, bisFlying);
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision", meta =(AllowPrivateAccess = "true"))
	class UCapsuleComponent* capsuleCollison;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Math")
	//class UText3DComponent* textRender;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* floorBox;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void setRandomNum(int32 randomNumGenerated);

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:

	UPROPERTY(BlueprintReadWrite)
	bool isFlying = false;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnIsFlyingChangedDelegate onMyEvent;


	UFUNCTION(BlueprintCallable)
	void getIsFlyingCallback();

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* uniqueCry;
};
