#include "DeathBlock.h"
#include "AirPilot.h"
#include "PaperSpriteComponent.h"

ADeathBlock::ADeathBlock()
{
    PrimaryActorTick.bCanEverTick = true;
    MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
    RootComponent = MySprite;
    MySprite->OnComponentHit.AddDynamic(this, &ADeathBlock::OnCollision);
}

void ADeathBlock::BeginPlay()
{
    Super::BeginPlay();
}

void ADeathBlock::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADeathBlock::OnCollision(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    if (OtherActor && OtherActor->IsA(AAirPilot::StaticClass()))
    {
        AAirPilot* AirPilot = Cast<AAirPilot>(OtherActor);
        if (AirPilot)
        {
            AirPilot->KillPilot();
        }
    }
}