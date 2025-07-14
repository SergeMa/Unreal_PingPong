#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	/** Bind widget references */
	virtual void NativeConstruct() override;

	/** Left player score text */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_LeftScore;

	/** Right player score text */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_RightScore;

public:
	/** Set left (white) score */
	UFUNCTION(BlueprintCallable)
	void SetLeftScore(int32 NewScore);

	/** Set right (blue) score */
	UFUNCTION(BlueprintCallable)
	void SetRightScore(int32 NewScore);
};
