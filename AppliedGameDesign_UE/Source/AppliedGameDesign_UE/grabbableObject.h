// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "GameFramework/Actor.h"
#include "grabbableObject.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIsFlyingChangedDelegate, bool, bisFlying);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlaySFX_Delegate, USoundBase*, uniqueCry);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Math")
	class UTextRenderComponent* textRender;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Math")
	class UTextRenderComponent* textRenderBackDrop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* floorBox;

	UFUNCTION()
	 void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	 void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void setRandomNum(int32 randomNumGenerated);




public:

	UPROPERTY(BlueprintReadWrite) bool isFlying = false;

	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnIsFlyingChangedDelegate onMyEvent;


	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnPlaySFX_Delegate playSFX_Event;


	UFUNCTION(BlueprintCallable) void getIsFlyingCallback();

	UFUNCTION(BlueprintCallable) void playSFXCallback();

	UPROPERTY(EditAnywhere, Category = "Audio") class USoundBase* uniqueCry;

	UPROPERTY(VisibleAnywhere) bool grabbableIsOdd;

	void set_grabbableIsOdd(bool _isOdd);
	bool get_grabbableIsOdd(); 
};
