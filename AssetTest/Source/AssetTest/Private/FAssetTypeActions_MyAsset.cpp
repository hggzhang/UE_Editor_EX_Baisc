// Fill out your copyright notice in the Description page of Project Settings.


#include "FAssetTypeActions_MyAsset.h"
#include "MyAsset.h"
#include "FMyAssetEditorToolkit.h"

FAssetTypeActions_MyAsset::FAssetTypeActions_MyAsset(EAssetTypeCategories::Type Type)
{
	MyAssetCategory = Type;
}

FText FAssetTypeActions_MyAsset::GetName() const
{
	return NSLOCTEXT("Editor", "My Assets", "MyTestAsset");
}

FColor FAssetTypeActions_MyAsset::GetTypeColor() const
{
	return FColor::Green;
}

UClass* FAssetTypeActions_MyAsset::GetSupportedClass() const
{
	return UMyAsset::StaticClass();
}

void FAssetTypeActions_MyAsset::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type ToolKitModeType = EditWithinLevelEditor ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjectIterator = InObjects.CreateConstIterator(); ObjectIterator; ++ObjectIterator)
	{
		if (UMyAsset* MAsset = Cast<UMyAsset>(*ObjectIterator))
		{
			const TSharedRef<FMyAssetEditorToolkit> RecoilAssetEditorToolKit = MakeShareable(new FMyAssetEditorToolkit());
			RecoilAssetEditorToolKit->InitializeAssetEditor(ToolKitModeType, EditWithinLevelEditor, MAsset);
		}
	}
	//FAssetTypeActions_Base::OpenAssetEditor(InObjects, EditWithinLevelEditor);
}

uint32 FAssetTypeActions_MyAsset::GetCategories()
{
	return MyAssetCategory;
}

