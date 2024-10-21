#include "PlayerPongBat.h"
#include "PongBall.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

APlayerPongBat::APlayerPongBat()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create audio component
    BackgroundMusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundMusicComponent"));
    BackgroundMusicComponent->SetupAttachment(RootComponent);
}

void APlayerPongBat::BeginPlay()
{
    Super::BeginPlay();

    if (BackgroundMusicCue)
    {
        BackgroundMusicComponent->SetSound(BackgroundMusicCue);
        BackgroundMusicComponent->Play();
    }
}

void APlayerPongBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    InputComponent->BindAxis("Vertical", this, &APlayerPongBat::MovePlayer);
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPongBat::MovePlayer(float input)
{
    SetActorLocation(GetActorLocation() + FVector(0, 0, 1 * input));
}

void APlayerPongBat::NotifyHit(
    class UPrimitiveComponent* MyComp,
    AActor* Other,
    class UPrimitiveComponent* OtherComp,
    bool bSelfMoved,
    FVector HitLocation,
    FVector HitNormal,
    FVector NormalImpulse,
    const FHitResult& Hit)
{
    APongBall* Ball = Cast<APongBall>(Other);
    if (Ball)
    {
        FVector BatLocation = GetActorLocation();
        float HitOffset = HitLocation.Z - BatLocation.Z;

        float DeflectionAngle = 0.0f;

        // Determine deflection based on HitOffset
        if (HitOffset > 150) DeflectionAngle = 1.0f; // High positive deflection (Red)
        else if (HitOffset > 100) DeflectionAngle = 0.75f; // Medium positive deflection (Orange)
        else if (HitOffset > 50) DeflectionAngle = 0.5f; // Low positive deflection (Yellow)
        else if (HitOffset > -50) DeflectionAngle = 0.0f; // No deflection (Green)
        else if (HitOffset > -100) DeflectionAngle = -0.5f; // Low negative deflection (Yellow)
        else if (HitOffset > -150) DeflectionAngle = -0.75f; // Medium negative deflection (Orange)
        else DeflectionAngle = -1.0f; // High negative deflection (Red)

        FVector BallVelocity = Ball->GetVelocity();
        BallVelocity.Z += DeflectionAngle * BallVelocity.Size();

        Ball->GetRootComponent()->ComponentVelocity = BallVelocity;
    }
}
