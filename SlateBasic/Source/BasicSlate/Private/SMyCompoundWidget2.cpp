
#include "SMyCompoundWidget2.h"

#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
FReply SMyCompoundWidget2::HandBtnClick()
{
	// 触发委托通知外部
	if (OnButtonClicked.IsBound())
	{
		OnButtonClicked.Execute();
	}
	return FReply::Handled();
}

// 设置文本的公开方法
void SMyCompoundWidget2::SetText(const FText& InText)
{
	MyText = InText;
	if (MyTextWidget.IsValid())
	{
		MyTextWidget->SetText(MyText);
	}
}

void SMyCompoundWidget2::Construct(const FArguments& InArgs)
{
	MyText = InArgs._InitText; //读取参数
	OnButtonClicked = InArgs._OnButtonClicked;
	ChildSlot
	[
		SNew(SVerticalBox) 
		+ SVerticalBox::Slot()
			. AutoHeight()
				. Padding(10)
					[
						SAssignNew(MyTextWidget, STextBlock)
							.Text(MyText)
							.Justification(ETextJustify::Center)
					]
		+ SVerticalBox::Slot()
			.AutoHeight()
				.Padding(10)
					[
						SNew(SButton)
							.Text(FText::FromString("Click Here"))
							.OnClicked_Raw(this, &SMyCompoundWidget2::HandBtnClick)
					]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
