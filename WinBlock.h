#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "AirPilot.h" // Include AirPilot header to use AAirPilot class

#include "WinBlock.generated.h"

UCLASS()
class MYPROJECTCW2_API AWinBlock : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AWinBlock();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, Category = "Sprites")
    class UPaperFlipbookComponent* MySprite;

    UFUNCTION() // Declare OnCollision function as UFUNCTION to bind it to collision event
        void OnCollision(
            UPrimitiveComponent* HitComponent,
            AActor* OtherActor,
            UPrimitiveComponent* OtherComp,
            FVector NormalImpulse,
            const FHitResult& Hit
        );
};
