#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "AirPilot.h" // Include AirPilot.h to access the AAirPilot class
#include "BaseEnemy1.generated.h"

UCLASS()
class MYPROJECTCW2_API ABaseEnemy1 : public APawn
{
    GENERATED_BODY()

public:
    ABaseEnemy1();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UPaperFlipbookComponent* MySprite;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UCapsuleComponent* MyBodyCollider;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UBoxComponent* LeftTrigger;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UBoxComponent* RightTrigger;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UBoxComponent* HeadTrigger;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float BounceForce; // Declare BounceForce here

    UFUNCTION()
    void OnBodyCollision(
        UPrimitiveComponent* HitComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        FVector NormalImpulse,
        const FHitResult& Hit
    );

    UFUNCTION()
    void OnHeadOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
};
