#include "DumbGoombah1.h"
#include "DeathBlock.h"
#include "Components/PrimitiveComponent.h"

ADumbGoombah1::ADumbGoombah1()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADumbGoombah1::BeginPlay()
{
    Super::BeginPlay();
}

void ADumbGoombah1::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MyBodyCollider->AddForce(FVector(-1, 0, 0) * EnemyHorizontalAcceleration);

    FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
    ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -EnemyMaxSpeed, EnemyMaxSpeed);
    MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);
}

void ADumbGoombah1::Die()
{
    Destroy();
}

void ADumbGoombah1::OnCollision(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    if (OtherActor && OtherActor->IsA(ADeathBlock::StaticClass())) // Check if OtherActor is a DeathBlock
    {
        Die(); // Call Die function to destroy the Goombah
    }
}
