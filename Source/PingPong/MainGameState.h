#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameState.generated.h"

/**
 * GameState class that stores and replicates the player scores.
 */
UCLASS()
class PINGPONG_API AMainGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(ReplicatedUsing = OnRep_ScoreChanged, BlueprintReadOnly, Category = "Score")
	int LeftScore = 0;

	UPROPERTY(ReplicatedUsing = OnRep_ScoreChanged, BlueprintReadOnly, Category = "Score")
	int RightScore = 0;

	/** Called on clients when scores are updated */
	UFUNCTION()
	void OnRep_ScoreChanged();

	/** Delegate triggered when score changes (for UI etc) */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnScoreChanged, int, int);
	FOnScoreChanged OnScoreChangedDelegate;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
