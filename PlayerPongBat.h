#pragma once

#include "CoreMinimal.h"
#include "BasePongBat.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "PlayerPongBat.generated.h"

/**
 *
 */
UCLASS()
class PORTFOLIO_API APlayerPongBat : public ABasePongBat
{
    GENERATED_BODY()

public:
    APlayerPongBat();

protected:
    virtual void BeginPlay() override;
    virtual void NotifyHit(
        class UPrimitiveComponent* MyComp,
        AActor* Other,
        class UPrimitiveComponent* OtherComp,
        bool bSelfMoved,
        FVector HitLocation,
        FVector HitNormal,
        FVector NormalImpulse,
        const FHitResult& Hit) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    void MovePlayer(float input);

private:
    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundCue* BackgroundMusicCue;

    UPROPERTY(VisibleAnywhere, Category = "Audio")
    UAudioComponent* BackgroundMusicComponent;
};
