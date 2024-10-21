#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "Components/CapsuleComponent.h"
#include "DumbGoombahs.generated.h"

/**
 *
 */
UCLASS()
class PORTFOLIO_API ADumbGoombahs : public ABaseEnemy
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Declare and initialize EnemyHorizontalAcceleration and EnemyMaxSpeed
    UPROPERTY(EditAnywhere, Category = "Enemy Properties")
    float EnemyHorizontalAcceleration = 1000;

    UPROPERTY(EditAnywhere, Category = "Enemy Properties")
    float EnemyMaxSpeed = 100;

};
