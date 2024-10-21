#include "AIPongBat.h"
#include "PongBall.h"
#include "Kismet/GameplayStatics.h"

void AAIPongBat::BeginPlay()
{
    Super::BeginPlay();
    TheBall = UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass());
}

void AAIPongBat::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!TheBall)
    {
        return;
    }

    FVector BallLocation = TheBall->GetActorLocation();
    FVector BatLocation = GetActorLocation();

    // Increase this value to make the bat move faster
    float Speed = 200.0f * DeltaTime;

    if (BatLocation.Z > BallLocation.Z)
    {
        SetActorLocation(FVector(BatLocation.X, BatLocation.Y, FMath::Max(BallLocation.Z, BatLocation.Z - Speed)));
    }
    else if (BatLocation.Z < BallLocation.Z)
    {
        SetActorLocation(FVector(BatLocation.X, BatLocation.Y, FMath::Min(BallLocation.Z, BatLocation.Z + Speed)));
    }
}

void AAIPongBat::NotifyHit(
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


