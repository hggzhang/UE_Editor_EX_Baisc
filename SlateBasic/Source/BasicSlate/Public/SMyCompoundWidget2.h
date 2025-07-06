// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class STextBlock;
class SButton;

DECLARE_DELEGATE(FOnBtnClicked)
 // 添加按钮点击委托
/**
 * 
 */
class BASICSLATE_API SMyCompoundWidget2 : public SCompoundWidget
{

private:
	TSharedPtr<STextBlock> MyTextWidget; // 引用，方便动态修改属性，SButton不需要动态修改
	FText MyText;
	FReply HandBtnClick();

public:
	// 注意InitText声明方式
	SLATE_BEGIN_ARGS(SMyCompoundWidget2) : _InitText(FText::FromString("Default"))
	{}
	SLATE_ARGUMENT(FText, InitText)
	SLATE_EVENT(FOnBtnClicked, OnButtonClicked) // 添加委托绑定
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// 公开设置文本的方法
	void SetText(const FText& InText);

	// 添加按钮点击委托
	FOnBtnClicked OnButtonClicked;
};
