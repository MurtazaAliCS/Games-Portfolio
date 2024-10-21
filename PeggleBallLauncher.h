#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "Engine/World.h" // Include this for accessing the World

#include "PeggleBallLauncher.generated.h"

UCLASS()
class PORTFOLIO_API APeggleBallLauncher : public APawn
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, Category = "Sprites")
    class UPaperSpriteComponent* MySprite;

    UPROPERTY(EditAnywhere, Category = "Ammo")
    TSubclassOf<AActor> BallBPClass;

    bool bIsBallInPlay; // Flag to indicate if a ball is in play
    bool bCanFire; // Flag to indicate if the launcher can fire a ball

    const float BottomOfScreenThreshold = -1000.0f; // Threshold to determine when a ball has left the bottom of the screen

public:
    // Sets default values for this pawn's properties
    APeggleBallLauncher();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

    void MovePlayer(float input);
    void Fire();
    void BallDestroyedOffScreen(); // Method to call when a ball is destroyed off the bottom of the screen
    void ReloadLauncher(); // Method to reload the launcher

    float ShotPower = 10000.0f;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
