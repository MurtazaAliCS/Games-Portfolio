#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Engine/EngineTypes.h"
#include "PeggleBlock.generated.h"

UCLASS()
class PORTFOLIO_API APeggleBlock : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APeggleBlock();

    UPROPERTY(VisibleAnywhere, Category = "Sprites")
    class UPaperSpriteComponent* MySprite;

    // Rotation speed of the block in degrees per second (for clock-like rotation)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
    float RotationSpeed = 90.0f;

    // Horizontal movement parameters
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float MovementSpeed; // Speed at which the block moves horizontally

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float MaxMovementDistance; // Maximum distance the block can move from the spawn point

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    FVector SpawnPoint; // Central spawn point around which the block moves

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
    FTimerHandle DestroyTimer;
    void DestroyThisObject();
};
