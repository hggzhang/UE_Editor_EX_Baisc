


#include "FAssetTypeActions_PreviewObject.h"
#include "UPreviewObject.h"
#include "FPreviewObjectEditorToolkit.h"

FAssetTypeActions_PreviewObject::FAssetTypeActions_PreviewObject(EAssetTypeCategories::Type Type)
{
	TypeCategories = Type;
}

FText FAssetTypeActions_PreviewObject::GetName() const
{
	return NSLOCTEXT("MyEditor", "MyPreviewObject", "MyPreviewObject");
}

uint32 FAssetTypeActions_PreviewObject::GetCategories()
{
	return TypeCategories;
}

FColor FAssetTypeActions_PreviewObject::GetTypeColor() const
{
	return FColor::Green;
}

UClass* FAssetTypeActions_PreviewObject::GetSupportedClass() const
{
	return UPreviewObject::StaticClass();
}

void FAssetTypeActions_PreviewObject::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type ToolKitModeType = EditWithinLevelEditor ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjectIterator = InObjects.CreateConstIterator(); ObjectIterator; ++ObjectIterator)
	{
		if (UPreviewObject* OurAsset = Cast<UPreviewObject>(*ObjectIterator))
		{
			const TSharedRef<FPreviewObjectEditorToolkit> RecoilAssetEditorToolKit = MakeShareable(new FPreviewObjectEditorToolkit());
			RecoilAssetEditorToolKit->InitializeAssetEditor(ToolKitModeType, EditWithinLevelEditor, OurAsset);
		}
	}
}
