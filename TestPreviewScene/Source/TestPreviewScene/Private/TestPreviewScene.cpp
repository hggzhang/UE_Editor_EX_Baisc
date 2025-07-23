// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestPreviewScene.h"
#include "AssetToolsModule.h"
#include "FAssetTypeActions_PreviewObject.h"

#define LOCTEXT_NAMESPACE "FTestPreviewSceneModule"

void FTestPreviewSceneModule::StartupModule()
{
	IAssetTools& AssetToolModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	const auto PreviewObjectCategory = AssetToolModule.RegisterAdvancedAssetCategory(FName(TEXT("MyAssets")), NSLOCTEXT("MyEditor", "PreviewObjectAssetName", "PreviewObjectAssetName"));
	const TSharedPtr<FAssetTypeActions_PreviewObject> PreviewObjectTypeAction = MakeShareable(new FAssetTypeActions_PreviewObject(PreviewObjectCategory));
	AssetToolModule.RegisterAssetTypeActions(PreviewObjectTypeAction.ToSharedRef());
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FTestPreviewSceneModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTestPreviewSceneModule, TestPreviewScene)