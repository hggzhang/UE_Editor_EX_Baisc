// Copyright Epic Games, Inc. All Rights Reserved.

#include "BasicSlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FBasicSlateStyle::StyleInstance = nullptr;

void FBasicSlateStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FBasicSlateStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FBasicSlateStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("BasicSlateStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

// Find the plugin path and create the style set with the icon
TSharedRef< FSlateStyleSet > FBasicSlateStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("BasicSlateStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("BasicSlate")->GetBaseDir() / TEXT("Resources"));

	Style->Set("BasicSlate.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FBasicSlateStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FBasicSlateStyle::Get()
{
	return *StyleInstance;
}
