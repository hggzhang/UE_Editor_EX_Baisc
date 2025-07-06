// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBtnClickEvent);

class SMyCompoundWidget2;

/**
 * 
 */
UCLASS(meta = (
	DisplayName = "MyUserWidget",
	Category = "Custom",
	PreviewIcon = "Icons.Cube"
))
class BASICSLATERUNTIME_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting")
	FText DisplayText;

	UFUNCTION(BlueprintCallable, Category = "MySetting")
	void SetDisplayText(const FString& InText);

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnBtnClickEvent OnBtnClicked;

	void HandClick();

	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SMyCompoundWidget2> MySlate;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
};
