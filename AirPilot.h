#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h" // Include for USoundCue
#include "TimerManager.h"
#include "AirPilot.generated.h"

UENUM()
enum class PilotAnimationState : uint8
{
    AS_FLAPPING,
    AS_IDLE,
    AS_DEAD,
    AS_DEATH
};

UCLASS()
class MYPROJECTCW2_API AAirPilot : public APawn
{
    GENERATED_BODY()

public:
    AAirPilot();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, Category = "Sprites")
    class UPaperFlipbookComponent* MySprite;

    UPROPERTY(VisibleAnywhere, Category = "Collider")
    class UCapsuleComponent* MyBodyCollider;

    UPROPERTY(VisibleAnywhere, Category = "Camera Setup")
    class USpringArmComponent* MySpringArm;

    UPROPERTY(VisibleAnywhere, Category = "Camera Setup")
    class UCameraComponent* MyCamera;

    UPROPERTY(EditAnywhere, Category = "Player Properties")
    float FlapForce = 1000;

    UPROPERTY(EditAnywhere, Category = "Player Properties")
    float GravityForce = 980;

    UPROPERTY(EditAnywhere, Category = "Player Properties")
    float HorizontalSpeed = 200;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* DeathSoundCue;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    class UPaperFlipbook* Flipbook_Flapping;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    class UPaperFlipbook* Flipbook_Idle;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    class UPaperFlipbook* Flipbook_Death;

    UPROPERTY(VisibleAnywhere, Category = "Animations")
    PilotAnimationState CurrentAnimationState;

    UPROPERTY(VisibleAnywhere, Category = "Animations")
    PilotAnimationState OldAnimationState;

    void Flap();
    void IdentifyAnimStates();
    void ProcessAnimStateMachine();
    void KillPilot();
    void OnDeathSoundTimerExpired();
    void BouncePilot(float force);
    void OnDeathTimerExpired();
    void GoToWinScreen();

    UFUNCTION()
    void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        FVector NormalImpulse, const FHitResult& Hit);

public:
    bool bIsAlive = true;

private:
    bool bHasFlapped = false;

    FTimerHandle DeathTimerHandle;
    FTimerHandle DeathSoundTimerHandle; // Add this line
};
