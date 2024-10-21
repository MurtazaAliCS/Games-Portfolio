#include "BreakableBlock.h"
#include "Coin.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABreakableBlock::ABreakableBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
	RootComponent = MySprite;
}

// Called when the game starts or when spawned
void ABreakableBlock::BeginPlay()
{
	Super::BeginPlay();

	MySprite->OnComponentBeginOverlap.AddDynamic(this, &ABreakableBlock::BeginOverlap);
}

// Called every frame
void ABreakableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABreakableBlock::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if hit from above
	if (OtherActor && OtherActor != this)
	{
		FVector OtherActorLocation = OtherActor->GetActorLocation();
		FVector MyLocation = GetActorLocation();
		FVector HitDirection = MyLocation - OtherActorLocation; // Ensure the hit direction is from above

		// Check if the hit is from above
		if (HitDirection.Z > 0 && FMath::Abs(HitDirection.Z) > FMath::Abs(HitDirection.X) && FMath::Abs(HitDirection.Z) > FMath::Abs(HitDirection.Y))
		{
			DestroyBlock();
		}
	}
}

void ABreakableBlock::DestroyBlock()
{
	if (CoinClass)
	{
		FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 50);
		FRotator SpawnRotation = GetActorRotation();
		GetWorld()->SpawnActor<ACoin>(CoinClass, SpawnLocation, SpawnRotation);
	}

	Destroy();
}
