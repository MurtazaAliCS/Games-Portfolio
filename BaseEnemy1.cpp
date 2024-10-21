#include "BaseEnemy1.h"
#include "PaperFlipbookComponent.h"
#include "AirPilot.h" // Include AirPilot.h to access the AAirPilot class

ABaseEnemy1::ABaseEnemy1()
{
    PrimaryActorTick.bCanEverTick = true;
    MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("My Image"));
    MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("My Body"));
    LeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Left Detector"));
    RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Right Detector"));
    HeadTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Head Detector"));

    RootComponent = MyBodyCollider;
    MySprite->SetupAttachment(RootComponent);
    LeftTrigger->SetupAttachment(RootComponent);
    RightTrigger->SetupAttachment(RootComponent);
    HeadTrigger->SetupAttachment(RootComponent);
}

void ABaseEnemy1::BeginPlay()
{
    Super::BeginPlay();
    MyBodyCollider->OnComponentHit.AddDynamic(this, &ABaseEnemy1::OnBodyCollision);
    HeadTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy1::OnHeadOverlap);
}

void ABaseEnemy1::OnBodyCollision(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    // Ensure collision with AirPilot
    if (OtherActor->IsA(AAirPilot::StaticClass()))
    {
        AAirPilot* Pilot = Cast<AAirPilot>(OtherActor);
        if (Pilot && Pilot->bIsAlive)
        {
            // Ensure the AirPilot is not already dead
            Pilot->KillPilot();
        }

        // Optionally destroy the enemy or disable its collision
        Destroy();
    }
}

void ABaseEnemy1::OnHeadOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    // Ensure collision with AirPilot
    if (OtherActor->IsA(AAirPilot::StaticClass()))
    {
        AAirPilot* Pilot = Cast<AAirPilot>(OtherActor);
        if (Pilot && Pilot->bIsAlive)
        {
            // Ensure the AirPilot is not already dead
            Pilot->KillPilot();
        }

        // Optionally destroy the enemy or disable its collision
        Destroy();
    }
}


void ABaseEnemy1::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABaseEnemy1::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // Super::SetupPlayerInputComponent(PlayerInputComponent);
    // You generally don't need to bind inputs for Pawns unless you have specific requirements.
}
