
#include "SMyCompoundWidget.h"

#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
FReply SMyCompoundWidget::HandBtnClick()
{
	MyText = FText::FromString("Btn Clicked!");
	MyTextWidget->SetText(MyText);
	return FReply::Handled();
}
void SMyCompoundWidget::Construct(const FArguments& InArgs)
{
	MyText = InArgs._InitText; //¶ÁÈ¡²ÎÊý
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
							.OnClicked_Raw(this, &SMyCompoundWidget::HandBtnClick)
					]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
