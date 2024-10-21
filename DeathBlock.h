#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathBlock.generated.h"

UCLASS()
class MYPROJECTCW2_API ADeathBlock : public AActor
{
    GENERATED_BODY()

public:
    ADeathBlock();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, Category = "Sprites")
    class UPaperSpriteComponent* MySprite;

    UFUNCTION()
    void OnCollision(
        UPrimitiveComponent* HitComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        FVector NormalImpulse,
        const FHitResult& Hit
    );
};
