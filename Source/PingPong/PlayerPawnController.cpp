#include "PlayerPawnController.h"
#include "GameFramework/GameStateBase.h"


void APlayerPawnController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GEngine)
	{
		if (AGameStateBase* GS = GetWorld()->GetGameState())
		{
			const int32 PlayerCount = GS->PlayerArray.Num();
			if (PlayerCount < 2)
			{
				const FString Message = FString::Printf(TEXT("Waiting for second player to connect"));
				GEngine->AddOnScreenDebugMessage(0, 0.f, FColor::Green, Message);
			}
		}
	}
}

