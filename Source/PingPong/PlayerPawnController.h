// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
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

	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	float MoveSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* MovementInputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveAction;

	void HandleMove(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void Server_HandleMove(float Axis);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_HandleMove(float Axis);

private:
	UPROPERTY()
	UScoreWidget* ScoreboardWidget;

	
};
