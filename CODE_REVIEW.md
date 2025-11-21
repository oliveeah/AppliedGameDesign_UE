# Code Review - Applied Game Design UE Project

## Overview
This document contains a comprehensive code review of the Unreal Engine 5.6 game project. The review covers code quality, potential bugs, performance considerations, and best practices.

---

## 1. TouchGameMode.cpp/h

### Critical Issues

#### Bug: checkIfLevelIsComplete() Logic Error (Line 41-46)
```cpp
bool ATouchGameMode::checkIfLevelIsComplete()
{
    UE_LOG(LogTemp, Display, TEXT("checkIFLevelIsComplete CALLED"));
    levelIsComplete = true;  // ❌ Always sets to true!
    return (oddIsFull && evenIsFull);
}
```
**Issue**: The function always sets `levelIsComplete = true` regardless of whether the level is actually complete.  
**Fix**: Should be `levelIsComplete = (oddIsFull && evenIsFull);`

### Code Quality Issues

#### 1. Commented Code (Line 20-21, 64)
```cpp
//ConstructorHelpers::FClassFinder<ASpectatorPawn> defaultCamera...
//	ACameraActor* cameraActor;
```
**Recommendation**: Remove commented code to improve readability.

#### 2. Random Seed Redundancy (Line 125)
```cpp
FMath::RandInit(FDateTime::Now().GetMillisecond());
```
**Issue**: Unreal Engine's RNG is already seeded. This could reduce randomness.  
**Recommendation**: Remove unless you have a specific reason for reseeding.

#### 3. Magic Numbers
```cpp
int32 randomNum = FMath::RandRange(1, 100);
```
**Recommendation**: Define constants:
```cpp
static constexpr int32 MIN_RANDOM_NUMBER = 1;
static constexpr int32 MAX_RANDOM_NUMBER = 100;
```

### Performance Concerns

#### Inefficient Set to Array Conversion (Line 98)
```cpp
TArray<int32> randomNumberArray = randomNumberTSet.Array();
```
**Note**: This creates a copy. Consider iterating directly if possible.

---

## 2. playerPawn.cpp/h

### Critical Issues

#### Missing Null Check (Line 81)
```cpp
playerController->GetMousePosition(mouseX, mouseY);
```
**Issue**: No null check before use (though checked earlier in BeginPlay).  
**Recommendation**: Add defensive check or ensure playerController is never null.

### Code Quality Issues

#### 1. Commented Code (Line 39, 191)
```cpp
//physicsHandle->SetupAttachment(root);
//currentlyGrabbedObject->setIsFlying(false);
```
**Recommendation**: Remove dead code.

#### 2. Magic Numbers (Line 93-94)
```cpp
const float LiftOffset = 150.0f;
// ...
worldLocation + worldDirection * 10000.f
```
**Recommendation**: Define as class constants with meaningful names:
```cpp
static constexpr float GRAB_LIFT_OFFSET = 150.0f;
static constexpr float GRAB_TRACE_DISTANCE = 10000.0f;
```

#### 3. Empty Else Blocks (Line 64-65, 118-120)
```cpp
else
{
}
```
**Recommendation**: Remove empty else blocks.

### Performance Concerns

#### SetActorTickEnabled Calls (Line 125, 180)
```cpp
SetActorTickEnabled(true);  // in interactCallbackHolding
SetActorTickEnabled(false); // in interactCallbackRelease
```
**Note**: This is actually good for performance! Only tick when needed.

---

## 3. grabbableObject.cpp/h

### Code Quality Issues

#### 1. Commented Code (Line 25-26, 109)
```cpp
//capsuleCollison->SetLinearDamping(0.f);
//bool isGrounded = false;
```
**Recommendation**: Remove commented code.

#### 2. Timer Delay Magic Number (Line 176)
```cpp
GetWorldTimerManager().SetTimer(groundedTimerHandle, this, &AgrabbableObject::clearTimer, 0.35f, false);
```
**Recommendation**: Define as a constant:
```cpp
static constexpr float GROUNDED_CHECK_DELAY = 0.35f;
```

#### 3. Disabled Tick with Override (Line 19, 61-64)
```cpp
PrimaryActorTick.bCanEverTick = false;
// ...
void AgrabbableObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
```
**Recommendation**: Remove the Tick function override if not used.

### Logic Concerns

#### Double Event Broadcast (Line 201, 208)
```cpp
getIsFlyingCallback(); // Broadcasts event
// ...
getIsFlyingCallback(); // Broadcasts again
```
**Note**: Intentional dual broadcast? Verify this is needed.

---

## 4. signs.cpp/h

### Critical Issues

#### Missing Null Check (Line 109, 144, 167, 179, 190)
```cpp
ATouchGameMode* gameMode = Cast<ATouchGameMode>(UGameplayStatics::GetGameMode(this));
if (gameMode)
{
    gameMode->OnSignAdded.Broadcast(this); // ✓ Good
}
// ...
gameMode->OnSignAdded.Broadcast(this); // ❌ Line 179 - no null check!
```
**Issue**: Lines 179 and 190 use `gameMode` without checking if the cast succeeded.  
**Fix**: Always check if `gameMode` is valid before calling methods.

### Code Quality Issues

#### 1. Repeated GameMode Access
```cpp
ATouchGameMode* gameMode = Cast<ATouchGameMode>(UGameplayStatics::GetGameMode(this));
```
**Recommendation**: Cache the game mode reference in BeginPlay:
```cpp
UPROPERTY()
ATouchGameMode* CachedGameMode;
```

#### 2. Commented Code (Line 180, 192)
```cpp
//onNewCollision.Broadcast();
//onRemovedCollision.Broadcast();
```
**Recommendation**: Either remove or use these delegates if needed.

#### 3. Verbose Logging
Extensive logging is good for debugging but may impact performance in shipping builds.  
**Recommendation**: Use `UE_LOG` with appropriate verbosity levels.

---

## 5. MyPlayerController.cpp/h

### Code Quality Issues

#### 1. Commented Code (Line 19)
```cpp
//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
```
**Recommendation**: Remove if not needed.

#### 2. Empty Implementation
The class only sets mouse cursor visibility. Consider:
- Is a custom controller class necessary?
- Could this be done in the pawn or game mode?

---

## 6. placementSlot.cpp/h

### Performance Issues

#### Unnecessary Ticking (Line 12, 33-37)
```cpp
PrimaryActorTick.bCanEverTick = true;
// ...
void AplacementSlot::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
```
**Issue**: Tick is enabled but does nothing.  
**Fix**: Set `PrimaryActorTick.bCanEverTick = false;` and remove Tick override.

---

## 7. grabbableObject_AC.cpp/h

### Code Quality Issues

#### Unused Component (Entire file)
```cpp
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class APPLIEDGAMEDESIGN_UE_API UgrabbableObject_AC : public UActorComponent
```
**Issue**: This component appears to be an empty template.  
**Recommendation**: Either implement it or remove the files if not needed.

---

## Overall Architecture Review

### Strengths ✅
1. **Good Separation of Concerns**: Each class has a clear responsibility
2. **Proper Use of UE Patterns**: Good use of UPROPERTY, UFUNCTION, delegates
3. **Physics Integration**: Nice physics handle implementation for grabbing
4. **Event System**: Good use of delegates for communication

### Areas for Improvement 📈

#### 1. Naming Conventions
- Inconsistent naming: `playerPawn` vs `AMyPlayerController` vs `AgrabbableObject` vs `Asigns`
- Recommendation: Follow Unreal Engine naming conventions consistently:
  - Classes: `APlayerPawn`, `ASignActor`, `AGrabbableObject`
  - Variables: `bIsOdd`, `NumberOfActors` (boolean prefix 'b', PascalCase for members)

#### 2. Code Organization
- Consider moving constants to a central config file
- Group related functionality (all physics code together, all collision handlers together)

#### 3. Documentation
- Add class-level and function-level documentation comments
- Document complex algorithms (like the random number generation logic)

#### 4. Error Handling
- Add more defensive programming (null checks, bounds checks)
- Consider what happens in edge cases (no signs, no objects, etc.)

---

## Security Considerations

### No Critical Security Issues Found ✅

Minor notes:
- Input validation is minimal but acceptable for a game project
- No network code to review
- No file I/O that could pose risks

---

## Summary & Priority Fixes

### High Priority 🔴
1. Fix `checkIfLevelIsComplete()` logic bug (TouchGameMode.cpp:44)
2. Add null checks for gameMode in signs.cpp (lines 179, 190)

### Medium Priority 🟡
1. Remove all commented code
2. Extract magic numbers to named constants
3. Fix naming convention inconsistencies
4. Remove unused grabbableObject_AC files if not needed
5. Disable unnecessary ticking in placementSlot

### Low Priority 🟢
1. Add documentation comments
2. Consider caching GameMode references
3. Remove empty else blocks
4. Improve logging verbosity levels

---

## Conclusion

Overall, this is a **solid Unreal Engine project** with good architecture and proper use of engine features. The main issues are:
- A few critical bugs that need fixing
- Code cleanliness (commented code, magic numbers)
- Naming consistency

The code demonstrates good understanding of UE5 patterns, and with the recommended fixes, it would be production-ready for a student/indie game project.

**Estimated Effort to Address Issues**: 2-4 hours

---

## Next Steps

1. Fix the critical bugs first (checkIfLevelIsComplete and null checks)
2. Run through the codebase and remove commented code
3. Extract constants and improve naming
4. Add basic documentation
5. Test thoroughly after changes

Good luck with your game development! 🎮
