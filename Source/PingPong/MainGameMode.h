// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	void Tick(float DeltaSeconds) override;

public:
	void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
	void ScoreGoal(int PlayerIndex);
};
