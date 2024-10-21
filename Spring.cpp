#include "Spring.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

// Sets default values
ASpring::ASpring()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the sprite component
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MySprite"));
	RootComponent = MySprite;

	// Initialize spring force
	SpringForce = 1000.0f;
}

// Called when the game starts or when spawned
void ASpring::BeginPlay()
{
	Super::BeginPlay();

	MySprite->OnComponentBeginOverlap.AddDynamic(this, &ASpring::BeginOverlap);
}

// Called every frame
void ASpring::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpring::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the other actor is valid and not itself
	if (OtherActor && OtherActor != this)
	{
		// Apply an upward force to the other actor
		UPrimitiveComponent* OtherActorComp = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
		if (OtherActorComp && OtherActorComp->IsSimulatingPhysics())
		{
			OtherActorComp->AddImpulse(FVector(0, 0, SpringForce), NAME_None, true);
		}
	}
}
