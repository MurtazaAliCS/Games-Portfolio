#include "PongBall.h"
#include "BasePongBat.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APongBall::APongBall()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
    RootComponent = MySprite;
    MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball Hit Box"));
    MyCollider->SetBoxExtent(FVector(32, 32, 32));
    MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    MyCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APongBall::BeginPlay()
{
    Super::BeginPlay();

    // Reset scores at the beginning of the game
    PlayerScore = 0;
    AIScore = 0;

    MyVelocity = FVector(300, 0, 300);

    HalfPlayFieldHeight = (2048 / 1.777) / 2;
    HalfPlayFieldWidth = (2048 / 2);

    MyCollider->OnComponentBeginOverlap.AddDynamic(this, &APongBall::OnCollision);
}

// Declare variables to keep track of scores
int32 PlayerScore = 0;
int32 AIScore = 0;

// Called every frame
void APongBall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector MyUpdatedLocation = GetActorLocation() + (MyVelocity * DeltaTime);

    if (MyUpdatedLocation.Z > HalfPlayFieldHeight)
    {
        MyVelocity.Z = -300;
    }
    else if (MyUpdatedLocation.Z < -HalfPlayFieldHeight)
    {
        MyVelocity.Z = 300;
    }

    if (MyUpdatedLocation.X > HalfPlayFieldWidth)
    {
        Score.Y += 1;
        // Player scored
        PlayerScore++;

        // Log the updated score
        UE_LOG(LogTemp, Warning, TEXT("Player scored: %d"), PlayerScore);

        // Check if the player score has reached 10
        if (PlayerScore >= 10)
        {
            UGameplayStatics::OpenLevel(this, "L_PongEndWin");
        }

        // Reset position to the middle
        MyUpdatedLocation.X = 0;
        MyUpdatedLocation.Y = 0;

        // Reset velocity
        MyVelocity = FVector(300, 0, FMath::RandBool() ? 300 : -300);
    }
    else if (MyUpdatedLocation.X < -HalfPlayFieldWidth)
    {
        Score.X += 1;
        // AI scored
        AIScore++;

        // Log the updated score
        UE_LOG(LogTemp, Warning, TEXT("AI scored: %d"), AIScore);

        // Check if the AI score has reached 10
        if (AIScore >= 10)
        {
            UGameplayStatics::OpenLevel(this, "L_PongEnd");
        }

        // Reset position to the middle
        MyUpdatedLocation.X = 0;
        MyUpdatedLocation.Y = 0;

        // Reset velocity
        MyVelocity = FVector(-300, 0, FMath::RandBool() ? 300 : -300);
    }

    SetActorLocation(MyUpdatedLocation);
}

void APongBall::OnCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("I HAVE HIT SOMETHING!"))
        FVector BatPosition = GetActorLocation();
    if (BatPosition.X > 0)
    {
        MyVelocity.X = -300;
    }
    else if (BatPosition.X < 0)
    {
        MyVelocity.X = 300;
    }
}
