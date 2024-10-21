#include "BreakoutBrick.h"
#include "Kismet/GameplayStatics.h"

ABreakoutBrick::ABreakoutBrick()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and set up the sprite component
    MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
    RootComponent = MySprite;

    // Initialize BrickBreakingSound
    BrickBreakingSound = nullptr; // Ensure initialization to nullptr
}

void ABreakoutBrick::BeginPlay()
{
    Super::BeginPlay();

    // Set initial health points for the brick based on its color
    SetBrickHealthPoints();
}

void ABreakoutBrick::SetBrickHealthPoints()
{
    // Set health points based on brick color
    switch (MyColor)
    {
    case EBrickColor::Blue:
        HealthPoints = 1;
        break;
    case EBrickColor::Green:
        HealthPoints = 2;
        break;
    case EBrickColor::Yellow:
        HealthPoints = 3;
        break;
    case EBrickColor::Red:
        HealthPoints = 4;
        break;
    case EBrickColor::Pink:
        HealthPoints = 5;
        break;
    case EBrickColor::Orange:
        HealthPoints = 6;
        break;
    case EBrickColor::Purple:
        HealthPoints = 9999999; // Purple bricks are indestructible
        break;
    }
}

void ABreakoutBrick::SubtractHealthPoints(int32 DamageAmount)
{
    // Check if the brick is not purple (indestructible)
    if (MyColor != EBrickColor::Purple)
    {
        HealthPoints -= DamageAmount;

        // Check if health points reached zero or less
        if (HealthPoints <= 0 && BrickBreakingSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, BrickBreakingSound, GetActorLocation());
            Destroy();
        }
    }
}

void ABreakoutBrick::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
