#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "signs.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNewCollision);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRemovedCollision);

// Forward declarations for engine component classes so this header compiles cleanly
class USceneComponent;
class UStaticMeshComponent;
class UTextRenderComponent;
class UBoxComponent;

UCLASS()
class APPLIEDGAMEDESIGN_UE_API Asigns : public AActor
{
    GENERATED_BODY()

public:
    Asigns();

protected:
    virtual void BeginPlay() override;

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* sceneRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* staticMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UTextRenderComponent* textRender;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UTextRenderComponent* textRenderBackDrop;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* boxCollider;

    UFUNCTION()
    void signs_OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void signs_OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
    virtual void Tick(float DeltaTime) override;

    // Public API
    UFUNCTION(BlueprintCallable, Category = "Sign")
    void setText(FText text);

    UFUNCTION(BlueprintCallable, Category = "Sign")
    void setIsOdd(bool _isOdd);

    UFUNCTION(BlueprintCallable, Category = "Sign")
    bool getIsOdd() const;

    UFUNCTION(BlueprintCallable, Category = "Sign")
    void setNumberOfActorsNeeded(int numberNeeded);

    void newCollision(bool isGrabbableOdd, bool isAdding);
    void removedCollision(bool isGrabbableOdd, bool isAdding);

    UPROPERTY(BlueprintAssignable, Category = "Delegates")
    FOnNewCollision onNewCollision;

    UPROPERTY(BlueprintAssignable, Category = "Delegates")
    FOnRemovedCollision onRemovedCollision;

    // Optional: let listeners sync current state
    UFUNCTION(BlueprintCallable, Category = "Sign")
    bool GetIsFull() const;

private:
    void checkIfProgressShouldBeUpdated(bool _isGrabbableOdd, bool isAdding);

    // State (single declarations only — avoids duplicate-definition errors)
    // Order here matches the constructor initializer order to avoid warnings.
    int32 numberOfOverlappedActors;
    int32 numberOfActorsInSceneNeeded;
    bool isOdd;

    // Tracks whether the sign currently meets the required amount (true = "full")
    bool bIsFull;
};