#include "AirPilot.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AAirPilot::AAirPilot()
{
    PrimaryActorTick.bCanEverTick = true;

    MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PilotBodySprite"));
    MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PilotBodyCapsule"));
    MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PilotSpringArm"));
    MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PilotBodyCamera"));

    RootComponent = MyBodyCollider;
    MySprite->SetupAttachment(RootComponent);
    MySpringArm->SetupAttachment(RootComponent);
    MyCamera->SetupAttachment(MySpringArm);

    MyBodyCollider->OnComponentHit.AddDynamic(this, &AAirPilot::OnCollision);

    bHasFlapped = false;
    MyBodyCollider->SetEnableGravity(false); // Disable gravity initially

    DeathSoundCue = nullptr; // Ensure this is assigned in the editor
}

void AAirPilot::BeginPlay()
{
    Super::BeginPlay();

    if (DeathSoundCue)
    {
        UE_LOG(LogTemp, Warning, TEXT("DeathSoundCue is initialized properly."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("DeathSoundCue is null! Please assign it in the editor."));
    }

    CurrentAnimationState = PilotAnimationState::AS_IDLE;
    OldAnimationState = PilotAnimationState::AS_DEAD;
    ProcessAnimStateMachine();
}

void AAirPilot::Flap()
{
    if (bIsAlive)
    {
        if (!bHasFlapped)
        {
            bHasFlapped = true;
            MyBodyCollider->SetEnableGravity(true); // Enable gravity after the first flap
        }

        MyBodyCollider->SetPhysicsLinearVelocity(FVector(0, 0, 0)); // Reset vertical velocity
        MyBodyCollider->AddImpulse(FVector(0, 0, 1) * FlapForce);
        CurrentAnimationState = PilotAnimationState::AS_FLAPPING;
        ProcessAnimStateMachine();
    }
}

void AAirPilot::IdentifyAnimStates()
{
    OldAnimationState = CurrentAnimationState;

    if (MyBodyCollider->GetPhysicsLinearVelocity().Z > 0)
    {
        CurrentAnimationState = PilotAnimationState::AS_FLAPPING;
    }
    else
    {
        CurrentAnimationState = PilotAnimationState::AS_IDLE;
    }
}

void AAirPilot::ProcessAnimStateMachine()
{
    if (CurrentAnimationState == OldAnimationState)
    {
        return;
    }

    switch (CurrentAnimationState)
    {
    case PilotAnimationState::AS_IDLE:
    {
        MySprite->SetFlipbook(Flipbook_Idle);
        break;
    }
    case PilotAnimationState::AS_FLAPPING:
    {
        MySprite->SetFlipbook(Flipbook_Flapping);
        break;
    }
    case PilotAnimationState::AS_DEATH:
    {
        MySprite->SetFlipbook(Flipbook_Death);
        UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
        UGameplayStatics::OpenLevel(GetWorld(), "L_GameOver");
        break;
    }
    }
}

void AAirPilot::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsAlive && bHasFlapped) // Only apply gravity and movement if the player has flapped
    {
        FVector Gravity(0, 0, -GravityForce * DeltaTime);
        MyBodyCollider->AddForce(Gravity);

        FVector HorizontalMovement(HorizontalSpeed * DeltaTime, 0, 0);
        MyBodyCollider->AddForce(HorizontalMovement, NAME_None, true);

        IdentifyAnimStates();
        ProcessAnimStateMachine();
    }
}

void AAirPilot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (bIsAlive)
    {
        PlayerInputComponent->BindAction("Flap", IE_Pressed, this, &AAirPilot::Flap);
    }
}

void AAirPilot::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("Collision Detected with %s"), *OtherActor->GetName());

    if (OtherActor->Tags.Contains("Obstacle") || OtherActor->Tags.Contains("Ground"))
    {
        UE_LOG(LogTemp, Warning, TEXT("Pilot should die now."));
        if (bIsAlive) // Check if the pilot is still alive to avoid multiple calls
        {
            KillPilot();
        }
    }
}

void AAirPilot::BouncePilot(float force)
{
    MyBodyCollider->AddImpulse(FVector(0, 0, force));
}

void AAirPilot::KillPilot()
{
    UE_LOG(LogTemp, Warning, TEXT("Pilot is Dead!"));

    // Check if the death sound cue is set
    if (DeathSoundCue)
    {
        UE_LOG(LogTemp, Warning, TEXT("Playing DeathSoundCue."));
        UGameplayStatics::PlaySoundAtLocation(this, DeathSoundCue, GetActorLocation());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("DeathSoundCue is null!"));
    }

    bIsAlive = false;

    // Set a timer for 0.2 seconds before switching to the game over state
    UE_LOG(LogTemp, Warning, TEXT("Setting death sound timer."));
    GetWorldTimerManager().SetTimer(DeathSoundTimerHandle, this, &AAirPilot::OnDeathSoundTimerExpired, 0.5f, false);

}

void AAirPilot::OnDeathSoundTimerExpired()
{
    UE_LOG(LogTemp, Warning, TEXT("Death sound timer expired. Updating animation state and setting death timer."));

    // Update the animation state to death
    CurrentAnimationState = PilotAnimationState::AS_DEATH;
    ProcessAnimStateMachine();

    // Set a timer for 1.8 seconds (2.0 - 0.2) before switching to the game over screen
    GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AAirPilot::OnDeathTimerExpired, 1.5f, false);
}

void AAirPilot::OnDeathTimerExpired()
{
    UE_LOG(LogTemp, Warning, TEXT("Death timer expired. Switching to Game Over screen."));
    UGameplayStatics::OpenLevel(GetWorld(), "L_GameOver");
}


void AAirPilot::GoToWinScreen()
{
    UGameplayStatics::OpenLevel(GetWorld(), "L_WinScreen");
}

