#include "PeggleBlock.h"
#include <PaperSpriteComponent.h>
#include "Engine/EngineTypes.h"
#include "Engine/World.h"

// Sets default values
APeggleBlock::APeggleBlock()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
    MySprite->OnComponentHit.AddDynamic(this, &APeggleBlock::OnHit);
    RootComponent = MySprite;

    // Initialize movement parameters
    MovementSpeed = 100.0f; // Adjust as needed
    MaxMovementDistance = 500.0f; // Adjust as needed
    SpawnPoint = GetActorLocation();
}

void APeggleBlock::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    MySprite->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void APeggleBlock::BeginPlay()
{
    Super::BeginPlay();
}

void APeggleBlock::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Calculate the amount of rotation for this frame based on the RotationSpeed
    float RotationThisFrame = RotationSpeed * DeltaTime;

    // Rotate the block around its X-axis (roll)
    AddActorLocalRotation(FRotator(RotationThisFrame, 0.0f, 0.0f));

    // Calculate the new location for this frame based on the MovementSpeed
    FVector NewLocation = GetActorLocation() + FVector(MovementSpeed * DeltaTime, 0.0f, 0.0f);

    // Check if the block has reached its maximum movement distance from the spawn point
    if ((NewLocation - SpawnPoint).Size() >= MaxMovementDistance)
    {
        // Reverse the movement direction
        MovementSpeed *= -1.0f;
    }

    // Set the new location
    SetActorLocation(NewLocation);
}


void APeggleBlock::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("HIT!*"));
    if (!DestroyTimer.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Setting Timer*"));
        GetWorld()->GetTimerManager().SetTimer(DestroyTimer,
            this,
            &APeggleBlock::DestroyThisObject,
            1.0,
            false);
    }
}

void APeggleBlock::DestroyThisObject()
{
    Destroy();
}
