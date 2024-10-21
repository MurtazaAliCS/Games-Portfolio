#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "BreakableBlock.generated.h"

UCLASS()
class PORTFOLIO_API ABreakableBlock : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABreakableBlock();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to handle overlap events
    UFUNCTION()
    void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // Function to destroy the block and spawn a coin
    void DestroyBlock();

private:
    // The sprite component for the block
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UPaperSpriteComponent* MySprite;

    // The coin class to spawn
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<class ACoin> CoinClass;
};


