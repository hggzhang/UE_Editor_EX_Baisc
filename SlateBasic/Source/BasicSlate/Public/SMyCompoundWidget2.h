// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class STextBlock;
class SButton;

DECLARE_DELEGATE(FOnBtnClicked)
 // ��Ӱ�ť���ί��
/**
 * 
 */
class BASICSLATE_API SMyCompoundWidget2 : public SCompoundWidget
{

private:
	TSharedPtr<STextBlock> MyTextWidget; // ���ã����㶯̬�޸����ԣ�SButton����Ҫ��̬�޸�
	FText MyText;
	FReply HandBtnClick();

public:
	// ע��InitText������ʽ
	SLATE_BEGIN_ARGS(SMyCompoundWidget2) : _InitText(FText::FromString("Default"))
	{}
	SLATE_ARGUMENT(FText, InitText)
	SLATE_EVENT(FOnBtnClicked, OnButtonClicked) // ���ί�а�
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// ���������ı��ķ���
	void SetText(const FText& InText);

	// ��Ӱ�ť���ί��
	FOnBtnClicked OnButtonClicked;
};
