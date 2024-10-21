#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h" // Include for USoundCue
#include "BreakoutBrick.generated.h"

UENUM(BlueprintType)
enum class EBrickColor : uint8
{
    Blue,
    Green,
    Yellow,
    Red,
    Pink,
    Orange,
    Purple
};

UCLASS()
class PORTFOLIO_API ABreakoutBrick : public AActor
{
    GENERATED_BODY()

public:
    ABreakoutBrick();

    virtual void BeginPlay() override;
    void SetBrickHealthPoints();
    void SubtractHealthPoints(int32 DamageAmount);
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Brick")
    int32 GetHealthPoints() const { return HealthPoints; }

protected:
    int32 HealthPoints;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brick")
    EBrickColor MyColor;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Brick")
    class UPaperSpriteComponent* MySprite;

    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class USoundCue* BrickBreakingSound; // Changed UAudioComponent* to USoundCue*
};
