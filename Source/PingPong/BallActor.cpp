#include "BallActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

// Конструктор
ABallActor::ABallActor()
{
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	RootComponent = BallMesh;

	BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BallMesh->SetCollisionProfileName(TEXT("BlockAll"));

	bReplicates = true;
	SetReplicateMovement(true);
}

// Ініціалізація на початку
void ABallActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		MoveDirection = UKismetMathLibrary::RandomUnitVector();
		MoveDirection.Z = 0.0f;
		MoveDirection.Normalize();
	}
}

void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector DeltaMove = MoveDirection * MoveSpeed;

	FHitResult Hit;
	AddActorWorldOffset(DeltaMove, true, &Hit);
	if (Hit.bBlockingHit)
	{
		FVector Normal = Hit.ImpactNormal;
		MoveDirection = ReflectVector(MoveDirection, Normal);
	}

	if(HasAuthority()) Multicast_UpdateBallPosition(GetActorLocation());
}

FVector ABallActor::ReflectVector(const FVector& Incoming, const FVector& Normal) const
{
	return Incoming - 2 * FVector::DotProduct(Incoming, Normal) * Normal;
}

void ABallActor::Multicast_UpdateBallPosition_Implementation(const FVector& NewLocation)
{
	SetActorLocation(NewLocation);
}

void ABallActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABallActor, MoveDirection);
}
