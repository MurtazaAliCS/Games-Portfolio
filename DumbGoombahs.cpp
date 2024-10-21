#include "DumbGoombahs.h"
#include "Components/CapsuleComponent.h"

void ADumbGoombahs::BeginPlay()
{
    Super::BeginPlay();
}

void ADumbGoombahs::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (MyBodyCollider)
    {
        FVector ForceToAdd = FVector(-1, 0, 0) * EnemyHorizontalAcceleration;
        MyBodyCollider->AddForce(ForceToAdd);

        FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
        ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -EnemyMaxSpeed, EnemyMaxSpeed);
        MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MyBodyCollider is not set in DumbGoombahs"));
    }
}
