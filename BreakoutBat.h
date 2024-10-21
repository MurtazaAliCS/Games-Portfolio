// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "BreakoutBat.generated.h"

UCLASS()
class PORTFOLIO_API ABreakoutBat : public APawn
{
	GENERATED_BODY()

public:
	void MovePlayer(float input);
	void SetPlayerInputComponent(UInputComponent* PlayerInputComponent);
	// Sets default values for this pawn's properties
	ABreakoutBat();


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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

