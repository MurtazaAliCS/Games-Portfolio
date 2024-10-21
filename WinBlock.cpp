#include "WinBlock.h"
#include "PaperFlipbookComponent.h"

// Sets default values
AWinBlock::AWinBlock()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MyImage"));
    RootComponent = MySprite;
    MySprite->OnComponentHit.AddDynamic(this, &AWinBlock::OnCollision); // Bind OnCollision function to component hit event
}

// Called when the game starts or when spawned
void AWinBlock::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AWinBlock::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWinBlock::OnCollision(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    // Check if the OtherActor is the AirPilot
    if (OtherActor && OtherActor->IsA(AAirPilot::StaticClass()))
    {
        // Cast to AAirPilot
        AAirPilot* AirPilot = Cast<AAirPilot>(OtherActor);
        if (AirPilot)
        {
            // Call the function to switch to the WinScreen level
            AirPilot->GoToWinScreen();
        }
    }
}
