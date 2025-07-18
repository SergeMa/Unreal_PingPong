#include "BallActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GoalActor.h"
#include "MainGameMode.h"

// �����������
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

// ������������ �� �������
void ABallActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		StartingPos = GetActorLocation();
		MoveDirection = UKismetMathLibrary::RandomUnitVector();
		MoveDirection.Z = 0.0f;
		MoveDirection.Normalize();
		BallMesh->OnComponentBeginOverlap.AddDynamic(this, &ABallActor::OnGoalOverlap);
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

void ABallActor::OnGoalOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;

	if (AGoalActor* OverlappingGoalActor = Cast<AGoalActor>(OtherActor))
	{
		if (AMainGameMode* GM = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GM->ScoreGoal(OverlappingGoalActor->PlayerIndex);
		}
		ResetBall();
	}
}

void ABallActor::ResetBall()
{
	SetActorLocation(StartingPos);

	MoveDirection = UKismetMathLibrary::RandomUnitVector();
	MoveDirection.Z = 0.0f;
	MoveDirection.Normalize();
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
