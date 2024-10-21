// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PaperSpriteComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakoutBat.h"
#include "BreakoutBrick.h"
#include "BreakoutBall.generated.h"

class ABreakoutBrick;
class ABreakoutBat;

UCLASS()
class PORTFOLIO_API ABreakoutBall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABreakoutBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperSpriteComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* MyCollider;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FVector MyVelocity;
	float HalfPlayFieldHeight;
	float HalfPlayFieldWidth;
	float HalfBallWidth;
	float BallHalfWidth;
	int BallSpeed;
};