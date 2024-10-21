#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Spring.generated.h"

UCLASS()
class PORTFOLIO_API ASpring : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpring();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Function to handle overlap events
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// The sprite component for the spring
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* MySprite;

	// Spring force
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spring", meta = (AllowPrivateAccess = "true"))
	float SpringForce;
};
