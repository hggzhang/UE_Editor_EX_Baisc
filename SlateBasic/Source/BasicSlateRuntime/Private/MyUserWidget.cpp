// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "SMyCompoundWidget2.h"

void UMyUserWidget::SetDisplayText(const FString& InText)
{
    DisplayText = FText::FromString(InText);
    if (MySlate.IsValid())
    {
        MySlate->SetText(DisplayText);
    }
}

void UMyUserWidget::HandClick()
{
    OnBtnClicked.Broadcast();
}

TSharedRef<SWidget> UMyUserWidget::RebuildWidget()
{
	MySlate = SNew(SMyCompoundWidget2)
        .InitText(DisplayText)
        .OnButtonClicked(FOnBtnClicked::CreateUObject(this, &UMyUserWidget::HandClick));
	return MySlate.ToSharedRef();
}

void UMyUserWidget::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);

    // 显式释放Slate资源，否则可能报错
    MySlate.Reset();
}