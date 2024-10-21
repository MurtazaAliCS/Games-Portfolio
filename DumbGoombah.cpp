// Fill out your copyright notice in the Description page of Project Settings.


#include "DumbGoombah.h"

// Sets default values
ADumbGoombah::ADumbGoombah()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADumbGoombah::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADumbGoombah::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADumbGoombah::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

