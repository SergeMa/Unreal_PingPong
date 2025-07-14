#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallActor.generated.h"

UCLASS()
class PINGPONG_API ABallActor : public AActor
{
	GENERATED_BODY()

public:
	ABallActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* BallMesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 800.f;

	UPROPERTY(Replicated)
	FVector MoveDirection;

	UFUNCTION()
	FVector ReflectVector(const FVector& Incoming, const FVector& Normal) const;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UpdateBallPosition(const FVector& NewLocation);
};
