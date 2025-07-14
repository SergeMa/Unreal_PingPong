#include "ScoreWidget.h"
#include "Components/TextBlock.h"
#include "MainGameState.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AMainGameState* GS = GetWorld()->GetGameState<AMainGameState>())
	{
		GS->OnScoreChangedDelegate.AddLambda([this](int32 Left, int32 Right)
			{
				SetLeftScore(Left);
				SetRightScore(Right);
			});


		SetLeftScore(GS->LeftScore);
		SetRightScore(GS->RightScore);
	}
}

void UScoreWidget::SetLeftScore(int NewScore)
{
	if (Text_LeftScore)
	{
		Text_LeftScore->SetText(FText::AsNumber(NewScore));
	}
}

void UScoreWidget::SetRightScore(int NewScore)
{
	if (Text_RightScore)
	{
		Text_RightScore->SetText(FText::AsNumber(NewScore));
	}
}