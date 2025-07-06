// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class STextBlock;
class SButton;

/**
 * 
 */
class BASICSLATE_API SMyCompoundWidget : public SCompoundWidget
{

private:
	TSharedPtr<STextBlock> MyTextWidget; // 引用，方便动态修改属性，SButton不需要动态修改
	FText MyText;
	FReply HandBtnClick();

public:
	// 注意InitText声明方式
	SLATE_BEGIN_ARGS(SMyCompoundWidget) : _InitText(FText::FromString("Click Btn"))
	{}
	SLATE_ARGUMENT(FText, InitText)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
