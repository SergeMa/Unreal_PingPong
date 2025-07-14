// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalActor.generated.h"

UCLASS()
class PINGPONG_API AGoalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalActor();

private:
	/** Collision box that detects ball */
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* GoalTrigger;

public:
	UPROPERTY(EditAnywhere)
	int PlayerIndex = 1;
};
