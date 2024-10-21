#include "Mario.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h" // Include this for using timers

AMario::AMario()
{
    PrimaryActorTick.bCanEverTick = true;

    MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MarioBodySprite"));
    MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MarioBodyCapsule"));
    MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MarioSpringArm"));
    MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MarioBodyCamera"));

    RootComponent = MyBodyCollider;
    MySprite->SetupAttachment(RootComponent);
    MySpringArm->SetupAttachment(RootComponent);
    MyCamera->SetupAttachment(MySpringArm);

    // Bind OnCollision to the OnComponentHit event of MyBodyCollider
    MyBodyCollider->OnComponentHit.AddDynamic(this, &AMario::OnCollision);
}

void AMario::BeginPlay()
{
    Super::BeginPlay();
    CurrentAnimationState = KnightAnimationState::AS_IDLE;
    OldAnimationState = KnightAnimationState::AS_DEAD;
    ProcessAnimStateMachine();
}

void AMario::MovePlayerHorizontal(float value)
{
    if (bIsAlive) // Only allow movement if Mario is alive
    {
        MyBodyCollider->AddForce(FVector(1, 0, 0) * value * PlayerAcceleration, NAME_None);
    }
}

void AMario::Jump()
{
    if (bIsAlive && !bIsJumping) // Only allow jumping if Mario is alive and not already jumping
    {
        MyBodyCollider->AddImpulse(FVector(0, 0, 1) * JumpForce);
        bIsJumping = true;
    }
}

void AMario::IdentifyAnimStates()
{
    OldAnimationState = CurrentAnimationState;

    float CurrentSpeed = MyBodyCollider->GetPhysicsLinearVelocity().X;
    if (CurrentSpeed > 5)
    {
        CurrentAnimationState = KnightAnimationState::AS_WALKING_RIGHT;
    }
    else if (CurrentSpeed < -5)
    {
        CurrentAnimationState = KnightAnimationState::AS_WALKING_LEFT;
    }
    else
    {
        CurrentAnimationState = KnightAnimationState::AS_IDLE;
    }
}

void AMario::ProcessAnimStateMachine()
{
    if (CurrentAnimationState == OldAnimationState)
    {
        return;
    }

    switch (CurrentAnimationState)
    {
    case KnightAnimationState::AS_IDLE:
    {
        MySprite->SetFlipbook(Flipbook_Idle);
        break;
    }
    case KnightAnimationState::AS_WALKING_RIGHT:
    {
        MySprite->SetFlipbook(Flipbook_WalkingRight);
        MySprite->SetRelativeRotation(FRotator(0, 0, 0));
        break;
    }
    case KnightAnimationState::AS_WALKING_LEFT:
    {
        MySprite->SetFlipbook(Flipbook_WalkingRight);
        MySprite->SetRelativeRotation(FRotator(0, 180, 0));
        break;
    }
    case KnightAnimationState::AS_DEATH: // Added case for death animation
    {
        MySprite->SetFlipbook(Flipbook_Death);
        // Optionally, add logic for transitioning to another state after death animation completes
        UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
        // Ensure this function is called when the timer expires
        UGameplayStatics::OpenLevel(GetWorld(), "L_GameOver");
        break;
    }
    }
}

void AMario::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsAlive) // Only allow actions if Mario is alive
    {
        FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
        ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -PlayerMaxSpeed, PlayerMaxSpeed);
        MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);

        IdentifyAnimStates();
        ProcessAnimStateMachine();
    }
}

void AMario::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (bIsAlive) // Only bind inputs if Mario is alive
    {
        PlayerInputComponent->BindAxis("HorizontalMario", this, &AMario::MovePlayerHorizontal);
        PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMario::Jump);
    }
}

void AMario::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor->Tags.Contains("Floor"))
    {
        bIsJumping = false; // Reset jump flag when landing on the floor
    }
}

void AMario::BounceMario(float force)
{
    MyBodyCollider->AddImpulse(FVector(0, 0, force));
}

void AMario::KillMario()
{
    UE_LOG(LogTemp, Warning, TEXT("Mario is Dead!"));

    // Set the animation state to death and play the death animation flipbook
    CurrentAnimationState = KnightAnimationState::AS_DEATH;
    ProcessAnimStateMachine();

    // Deactivate input bindings
    bIsAlive = false;

    // Set a timer for 0.5 seconds before switching to the game over screen
    GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AMario::OnDeathTimerExpired, 0.5f, false);
}

void AMario::OnDeathTimerExpired()
{
    UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
    // Ensure this function is called when the timer expires
    UGameplayStatics::OpenLevel(GetWorld(), "L_GameOver");
}

void AMario::GoToWinScreen()
{
    // Transition to the WinScreen level
    UGameplayStatics::OpenLevel(GetWorld(), "L_WinScreen");
}
