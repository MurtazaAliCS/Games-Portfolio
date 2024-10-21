#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h" // Assuming ADumbGoombah1 inherits from ABaseEnemy
#include "DumbGoombah1.generated.h"

UCLASS()
class PORTFOLIO_API ADumbGoombah1 : public ABaseEnemy // Assuming ADumbGoombah1 inherits from ABaseEnemy
{
    GENERATED_BODY()

public:
    ADumbGoombah1();

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
