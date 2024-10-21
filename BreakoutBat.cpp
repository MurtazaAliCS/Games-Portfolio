// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakoutBat.h"
#include "BreakoutBall.h"
#include "Components/BoxComponent.h"
#include "BreakoutBat.h"
#include <Perception/AIPerceptionComponent.h>


void ABreakoutBat::MovePlayer(float input)
{
	float Speed = 1.0f;
	FVector Movement = FVector(input * Speed, 0, 0);
	
	SetActorLocation(GetActorLocation() + Movement);

}

void ABreakoutBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InputComponent->BindAxis("Horizontal", this, &ABreakoutBat::MovePlayer);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
// Sets default values
ABreakoutBat::ABreakoutBat()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;
	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball Hit Box"));
	MyCollider->SetBoxExtent(FVector(64, 4, 16));
	MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MyCollider->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABreakoutBat::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABreakoutBat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
