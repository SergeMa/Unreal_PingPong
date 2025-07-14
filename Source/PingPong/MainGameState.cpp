#include "MainGameState.h"
#include "Net/UnrealNetwork.h"

void AMainGameState::OnRep_ScoreChanged()
{
	OnScoreChangedDelegate.Broadcast(LeftScore, RightScore);
}

void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGameState, LeftScore);
	DOREPLIFETIME(AMainGameState, RightScore);
}
