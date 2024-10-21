#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Mario.generated.h"

UENUM()
enum class KnightAnimationState : uint8
{
    AS_WALKING_RIGHT,
    AS_WALKING_LEFT,
    AS_IDLE,
    AS_DEAD,
    AS_DEATH
};

UCLASS()
class PORTFOLIO_API AMario : public APawn
{
    GENERATED_BODY()

public:
    AMario();

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
    float JumpForce = 1000;

    UPROPERTY(EditAnywhere, Category = "Player Properties")
    float PlayerAcceleration = 1000;

    UPROPERTY(EditAnywhere, Category = "Player Properties")
    float PlayerMaxSpeed = 32;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    class UPaperFlipbook* Flipbook_WalkingRight;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    class UPaperFlipbook* Flipbook_Idle;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    class UPaperFlipbook* Flipbook_Death; // Added death animation flipbook

    UPROPERTY(VisibleAnywhere, Category = "Animations")
    KnightAnimationState CurrentAnimationState;

    UPROPERTY(VisibleAnywhere, Category = "Animations")
    KnightAnimationState OldAnimationState;

    void MovePlayerHorizontal(float value);
    void Jump();
    void IdentifyAnimStates();
    void ProcessAnimStateMachine();
    void BounceMario(float force);
    void KillMario();
    void OnDeathTimerExpired(); // Declaration of the missing member function
    void GoToWinScreen(); // Declaration to transition to WinScreen

    // Collision function declaration
    UFUNCTION()
    void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        FVector NormalImpulse, const FHitResult& Hit);

private:
    bool bIsJumping = false;
    bool bIsAlive = true; // Added bIsAlive variable

    FTimerHandle DeathTimerHandle; // Timer handle for death animation
};
