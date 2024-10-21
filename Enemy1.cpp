#include "Enemy1.h"
#include "DeathBlock.h"
#include "Components/PrimitiveComponent.h"
#include "AirPilot.h" // Include AirPilot.h to access the static flag

AEnemy1::AEnemy1()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEnemy1::BeginPlay()
{
    Super::BeginPlay();
}

void AEnemy1::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Only move if the player has flapped
    if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::SpaceBar))
    {
        // Add horizontal movement to the enemy
        MyBodyCollider->AddForce(FVector(-1, 0, 0) * EnemyHorizontalAcceleration);

        // Clamp the speed to avoid excessive movement
        FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
        ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -EnemyMaxSpeed, EnemyMaxSpeed);
        MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);
    }
}


void AEnemy1::Die()
{
    Destroy();
}

void AEnemy1::OnCollision(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    if (OtherActor && OtherActor->IsA(ADeathBlock::StaticClass())) // Check if OtherActor is a DeathBlock
    {
        Die(); // Call Die function to destroy the Enemy
    }
}
