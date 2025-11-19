#include "signs.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "grabbableObject.h"
#include "TouchGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/Engine.h"

// Sets default values
Asigns::Asigns()
    : numberOfOverlappedActors(0)
    , numberOfActorsInSceneNeeded(0)
    , isOdd(false)
    , bIsFull(false)
{
    PrimaryActorTick.bCanEverTick = true;

    sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("rootComponent"));
    SetRootComponent(sceneRoot);

    staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
    staticMesh->SetupAttachment(sceneRoot);

    textRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("textRender"));
    textRender->SetupAttachment(sceneRoot);

    textRenderBackDrop = CreateDefaultSubobject<UTextRenderComponent>(TEXT("textRenderBackDrop"));
    textRenderBackDrop->SetupAttachment(sceneRoot);

    boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("boxCollision"));
    boxCollider->SetupAttachment(sceneRoot);
}

void Asigns::BeginPlay()
{
    Super::BeginPlay();

    boxCollider->OnComponentBeginOverlap.AddDynamic(this, &Asigns::signs_OverlapBegin);
    boxCollider->OnComponentEndOverlap.AddDynamic(this, &Asigns::signs_OverlapEnd);

    UE_LOG(LogTemp, Display, TEXT("Asigns::BeginPlay: initial count=%d needed=%d isOdd=%d bIsFull=%d"),
        numberOfOverlappedActors, numberOfActorsInSceneNeeded, (int)isOdd, (int)bIsFull);
}

void Asigns::signs_OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    // Kept empty because AgrabbableObject calls newCollision directly.
}

void Asigns::signs_OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // Kept empty because AgrabbableObject calls removedCollision directly.
}

void Asigns::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void Asigns::setText(FText text)
{
    textRender->SetText(text);
    textRenderBackDrop->SetText(text);
}

void Asigns::setIsOdd(bool _isOdd)
{
    isOdd = _isOdd;
}

bool Asigns::getIsOdd() const
{
    return isOdd;
}

bool Asigns::GetIsFull() const
{
    return bIsFull;
}

void Asigns::setNumberOfActorsNeeded(int numberNeeded)
{
    numberOfActorsInSceneNeeded = numberNeeded;
    UE_LOG(LogTemp, Display, TEXT("Asigns::setNumberOfActorsNeeded: sign=%s needed=%d"), *GetName(), numberOfActorsInSceneNeeded);
}

void Asigns::newCollision(bool grabbableIsOdd, bool isAdding)
{
    // increment and clamp
    numberOfOverlappedActors = FMath::Max(0, numberOfOverlappedActors + 1);

    UE_LOG(LogTemp, Display, TEXT("Asigns::newCollision: sign=%s isOdd=%d grabbableIsOdd=%d count=%d needed=%d"),
        *GetName(), (int)isOdd, (int)grabbableIsOdd, numberOfOverlappedActors, numberOfActorsInSceneNeeded);

    // Broadcast every time a matching grabbable is added
    // checkIfProgressShouldBeUpdated already checks the parity (_isGrabbableOdd == isOdd)
    checkIfProgressShouldBeUpdated(grabbableIsOdd, true);

    // Keep the existing "full" tracking for GameMode and one-time full transition
    if (numberOfActorsInSceneNeeded > 0 && numberOfOverlappedActors >= numberOfActorsInSceneNeeded && !bIsFull)
    {
        bIsFull = true;
        UE_LOG(LogTemp, Display, TEXT("Asigns::newCollision: sign=%s reached full"), *GetName());

        ATouchGameMode* gameMode = Cast<ATouchGameMode>(UGameplayStatics::GetGameMode(this));
        if (gameMode)
        {
            if (isOdd)
            {
                gameMode->setIsOddFull(true);
            }
            else
            {
                gameMode->setIsEvenFull(true);
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("Asigns::newCollision: not yet full or already full (bIsFull=%d)"), (int)bIsFull);
    }
}

void Asigns::removedCollision(bool grabbableIsOdd, bool isAdding)
{
    // decrement and clamp to >= 0
    numberOfOverlappedActors = FMath::Max(0, numberOfOverlappedActors - 1);

    UE_LOG(LogTemp, Display, TEXT("Asigns::removedCollision: sign=%s isOdd=%d grabbableIsOdd=%d count=%d needed=%d"),
        *GetName(), (int)isOdd, (int)grabbableIsOdd, numberOfOverlappedActors, numberOfActorsInSceneNeeded);

    // Broadcast every time a matching grabbable is removed
    // Again, checkIfProgressShouldBeUpdated will only actually broadcast when parity matches.
    checkIfProgressShouldBeUpdated(grabbableIsOdd, false);

    // If we were full and fell below the threshold, clear the full state and update GameMode
    if (bIsFull && numberOfOverlappedActors < numberOfActorsInSceneNeeded)
    {
        bIsFull = false;
        ATouchGameMode* gameMode = Cast<ATouchGameMode>(UGameplayStatics::GetGameMode(this));
        if (gameMode)
        {
            if (isOdd)
            {
                UE_LOG(LogTemp, Display, TEXT("Asigns::removedCollision: odd requirement NOT met"));
                gameMode->setIsOddFull(false);
            }
            else
            {
                UE_LOG(LogTemp, Display, TEXT("Asigns::removedCollision: even requirement NOT met"));
                gameMode->setIsEvenFull(false);
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("Asigns::removedCollision: still not below threshold or wasn't full (bIsFull=%d)"), (int)bIsFull);
    }
}

void Asigns::checkIfProgressShouldBeUpdated(bool _isGrabbableOdd, bool isAdding)
{
    if (_isGrabbableOdd == isOdd)
    {
        if (isAdding)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("broadcasting added collision"));
            }
            onNewCollision.Broadcast();
        }
        else
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("broadcasting removed collision"));
            }
            onRemovedCollision.Broadcast();
        }
    }
}