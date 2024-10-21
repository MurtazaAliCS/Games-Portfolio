#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy1.h"
#include "AirPilot.h" // Include AirPilot.h to access the static flag
#include "Enemy1.generated.h"

UCLASS()
class MYPROJECTCW2_API AEnemy1 : public ABaseEnemy1
{
    GENERATED_BODY()

public:
    AEnemy1();

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    // Function to handle Goombah's death
    void Die();

    // Function declaration for collision handling
    UFUNCTION()
    void OnCollision(
        UPrimitiveComponent* HitComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        FVector NormalImpulse,
        const FHitResult& Hit
    );

private:
    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    float EnemyHorizontalAcceleration = 1000.f;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    float EnemyMaxSpeed = 400.f;
};
