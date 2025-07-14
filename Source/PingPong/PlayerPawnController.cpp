#include "PlayerPawnController.h"
#include "GameFramework/GameStateBase.h"
#include "ScoreWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerInput.h"
#include "PlayerPawn.h"


void APlayerPawnController::BeginPlay()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (MovementInputMappingContext)
		{
			Subsystem->AddMappingContext(MovementInputMappingContext, 0);
		}
	}

	if (IsLocalController() && ScoreboardWidgetClass)
	{
		ScoreboardWidget = CreateWidget<UScoreWidget>(this, ScoreboardWidgetClass);
		if (ScoreboardWidget)
		{
			ScoreboardWidget->AddToViewport();
		}
	}

}

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

void APlayerPawnController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPawnController::HandleMove);
	}
}

void APlayerPawnController::HandleMove(const FInputActionValue& Value)
{
	float Axis = Value.Get<float>();
	Server_HandleMove(Axis);
}

void APlayerPawnController::Server_HandleMove_Implementation(float Axis)
{
	Multicast_HandleMove(Axis);
}

void APlayerPawnController::Multicast_HandleMove_Implementation(float Axis)
{
	if (APawn* ControlledPawn = GetPawn())
	{
		FVector Movement = ControlledPawn->GetActorRightVector() * Axis * MoveSpeed * GetWorld()->GetDeltaSeconds();
		FVector NewLocation = ControlledPawn->GetActorLocation() + Movement;

		ControlledPawn->SetActorLocation(NewLocation, true);
	}
}