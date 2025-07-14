// MainGameMode.cpp

#include "MainGameMode.h"
#include "PlayerPawn.h"
#include "PlayerPawnController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/GameState.h"
#include "BallActor.h"

bool bBallSpawned = false;

void AMainGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!HasAuthority()) return;

    AGameStateBase* CurrentGameState = GameState;
    if (!CurrentGameState)
    {
        UE_LOG(LogTemp, Warning, TEXT("GameState not valid!"));
        return;
    }

    int32 NumPlayers = CurrentGameState->PlayerArray.Num();

    if (NumPlayers < 2)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Yellow,TEXT("Waiting on other player"));
        }
    }
    else if (!bBallSpawned)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            FVector SpawnLocation(0.f, 0.f, 350.f);
            FRotator SpawnRotation = FRotator::ZeroRotator;

            World->SpawnActor<ABallActor>(BallClass, SpawnLocation, SpawnRotation);
            bBallSpawned = true;
        }
    }
}

void AMainGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if (!HasAuthority() || !NewPlayer)
    {
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStarts);

    if (PlayerStarts.Num() < 2)
    {
        UE_LOG(LogTemp, Warning, TEXT("Not enough PlayerStart actors found!"));
        return;
    }

    AGameStateBase* CurrentGameState = GameState;
    if (!CurrentGameState)
    {
        UE_LOG(LogTemp, Warning, TEXT("GameState not valid!"));
        return;
    }

    int32 NumPlayers = CurrentGameState->PlayerArray.Num();
    int32 SpawnIndex = FMath::Clamp(NumPlayers - 1, 0, PlayerStarts.Num() - 1);


    APlayerStart* ChosenStart = Cast<APlayerStart>(PlayerStarts[SpawnIndex]);
    if (!ChosenStart)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerStart cast failed at index %d"), SpawnIndex);
        return;
    }

    APawn* NewPawn = World->SpawnActor<APawn>(DefaultPawnClass, ChosenStart->GetActorTransform());

    if (NewPawn)
    {
        NewPlayer->Possess(NewPawn);
    }
}