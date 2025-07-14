// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerPawnController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APlayerPawnController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;


	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UScoreWidget> ScoreboardWidgetClass;

private:
	UPROPERTY()
	UScoreWidget* ScoreboardWidget;
};
