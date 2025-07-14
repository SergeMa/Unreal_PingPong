// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerPawn.generated.h"

UCLASS()
class PINGPONG_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* Camera;

private:
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


public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
