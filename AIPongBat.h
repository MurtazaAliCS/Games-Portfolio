#pragma once

#include "CoreMinimal.h"
#include "BasePongBat.h"
#include "AIPongBat.generated.h"

/**
 *
 */
UCLASS()
class PORTFOLIO_API AAIPongBat : public ABasePongBat
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, Category = "ReferencedActors")
    class AActor* TheBall;

public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void NotifyHit(
        class UPrimitiveComponent* MyComp,
        AActor* Other,
        class UPrimitiveComponent* OtherComp,
        bool bSelfMoved,
        FVector HitLocation,
        FVector HitNormal,
        FVector NormalImpulse,
        const FHitResult& Hit) override;
};
