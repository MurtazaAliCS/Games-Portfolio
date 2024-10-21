#include "PeggleBallLauncher.h"
#include "EngineUtils.h" // Include this for TActorIterator

APeggleBallLauncher::APeggleBallLauncher()
{
    PrimaryActorTick.bCanEverTick = true;
    MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
    RootComponent = MySprite;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    bIsBallInPlay = false;
    bCanFire = true;
}

void APeggleBallLauncher::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    MySprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MySprite->TranslucencySortPriority = 3;
}

void APeggleBallLauncher::MovePlayer(float input)
{
    SetActorRotation(GetActorRotation() + FRotator(1 * input, 0, 0));
}

void APeggleBallLauncher::Fire()
{
    if (bCanFire)
    {
        UE_LOG(LogTemp, Warning, TEXT("Firing!"));
        AActor* SpawnedBall = GetWorld()->SpawnActor<AActor>(BallBPClass, GetActorLocation(), GetActorRotation());
        FVector ShotDirection = GetActorUpVector() *= -1;
        SpawnedBall->GetComponentByClass<UPaperSpriteComponent>()->AddImpulse(ShotDirection * ShotPower);

        bIsBallInPlay = true;
        bCanFire = false;
    }
}

void APeggleBallLauncher::BallDestroyedOffScreen()
{
    ReloadLauncher();
    bCanFire = true;
}

void APeggleBallLauncher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    InputComponent->BindAxis("Horizontal", this, &APeggleBallLauncher::MovePlayer);
    InputComponent->BindAction("Fire", IE_Pressed, this, &APeggleBallLauncher::Fire);
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APeggleBallLauncher::BeginPlay()
{
    Super::BeginPlay();
}

void APeggleBallLauncher::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsBallInPlay)
    {
        for (TActorIterator<AActor> ActorItr(GetWorld(), AActor::StaticClass()); ActorItr; ++ActorItr)
        {
            if (ActorItr->GetName().Contains("Ball"))
            {
                FVector ActorLocation = ActorItr->GetActorLocation();
                if (ActorLocation.Z < BottomOfScreenThreshold) // Check if the ball's Z-coordinate is below the bottom of the screen
                {
                    ActorItr->Destroy();
                    bIsBallInPlay = false;
                    BallDestroyedOffScreen();
                    break;
                }
            }
        }
    }
}

void APeggleBallLauncher::ReloadLauncher()
{
    // Implement reloading logic here, such as resetting the launcher's position.
}
