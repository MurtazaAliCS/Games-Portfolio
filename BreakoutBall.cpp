// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakoutBall.h"
#include "BreakoutBat.h"
#include "BreakoutBrick.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Camera/CameraComponent.h>
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraActor.h"
#include "CoreMinimal.h"

// Sets default values
ABreakoutBall::ABreakoutBall()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
    RootComponent = MySprite;
    MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball Hit Box"));
    MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    MyCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABreakoutBall::BeginPlay()
{
    Super::BeginPlay();

    BallHalfWidth = MySprite->Bounds.GetBox().GetSize().X / 2;
    MyCollider->SetBoxExtent(FVector(BallHalfWidth, BallHalfWidth, BallHalfWidth));

    MyVelocity = FVector(300, 0, 300);

    AActor* GameCamera = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
    UCameraComponent* GameCameraComponent = Cast<ACameraActor>(GameCamera)->GetCameraComponent();
    HalfPlayFieldHeight = (GameCameraComponent->OrthoWidth / GameCameraComponent->AspectRatio) / 2;
    HalfPlayFieldWidth = (GameCameraComponent->OrthoWidth / 2);

    BallSpeed = 300;

    MyCollider->OnComponentBeginOverlap.AddDynamic(this, &ABreakoutBall::OnCollision);
}

void ABreakoutBall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FVector MyUpdatedLocation = GetActorLocation() + (MyVelocity * DeltaTime);

    if (MyUpdatedLocation.Z + HalfBallWidth > HalfPlayFieldHeight)
    {
        MyVelocity.Z = -BallSpeed;
    }
    else if (MyUpdatedLocation.Z - HalfBallWidth < -HalfPlayFieldHeight)
    {
        // If the ball goes below the bottom of the playfield, destroy it
        Destroy();
        return;
    }

    if (MyUpdatedLocation.X + HalfBallWidth > HalfPlayFieldWidth)
    {
        MyVelocity.X = -BallSpeed;
    }
    else if (MyUpdatedLocation.X - HalfBallWidth < -HalfPlayFieldWidth)
    {
        MyVelocity.X = BallSpeed;
    }

    SetActorLocation(MyUpdatedLocation, false, NULL, ETeleportType::TeleportPhysics);
}

void ABreakoutBall::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
    if (OtherActor->IsA(ABreakoutBat::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("I HIT THE BAT!"));
        FVector BatPosition = GetActorLocation();
        MyVelocity.Z = BallSpeed;
    }
    else if (OtherActor->IsA(ABreakoutBrick::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("I HIT A BRICK!"));

        // Cast OtherActor to ABreakoutBrick and call SubtractHealthPoints method
        ABreakoutBrick* Brick = Cast<ABreakoutBrick>(OtherActor);
        if (Brick)
        {
            // Subtract health points from the brick
            Brick->SubtractHealthPoints(1);

            // Check if the brick is destroyed
            if (Brick->GetHealthPoints() <= 0)
            {
                // Destroy the brick
                Brick->Destroy();
            }
        }
    }

    FVector HitDirection = GetActorLocation() - OtherActor->GetActorLocation();
    HitDirection.Normalize();
    if (FMath::Abs(HitDirection.X) > FMath::Abs(HitDirection.Z))
    {
        if (HitDirection.X > 0)
        {
            MyVelocity.X = BallSpeed;
        }
        else if (HitDirection.X < 0)
        {
            MyVelocity.X = -BallSpeed;
        }
    }
    else
    {
        if (HitDirection.Z > 0)
        {
            MyVelocity.Z = BallSpeed;
        }
        else if (HitDirection.Z < 0)
        {
            MyVelocity.Z = -BallSpeed;
        }
    }
}



