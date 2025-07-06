// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetTest.h"
#include "AssetToolsModule.h"
#include "FAssetTypeActions_MyAsset.h"
#define LOCTEXT_NAMESPACE "FAssetTestModule"

void FAssetTestModule::StartupModule()
{
	RegisterAssetsAction();
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FAssetTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

// get the AssetTools module and register the asset type actions
void FAssetTestModule::RegisterAssetsAction() const
{
	IAssetTools& AssetToolModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	const auto Category = AssetToolModule.RegisterAdvancedAssetCategory(FName(TEXT("MyAsset")), NSLOCTEXT("Editor", "MyAssetMenuCategory", "MyAssetCategory"));
	const TSharedPtr<FAssetTypeActions_MyAsset> AssetsTypeAction = MakeShareable(new FAssetTypeActions_MyAsset(Category));
	AssetToolModule.RegisterAssetTypeActions(AssetsTypeAction.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetTestModule, AssetTest)