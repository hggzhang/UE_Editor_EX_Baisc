

#pragma once

#include "CoreMinimal.h"

class UPreviewObject;

class TESTPREVIEWSCENE_API FPreviewObjectEditorToolkit : public FAssetEditorToolkit
{
public:

	/** Begin FAssetEditorToolkit Interface */

	FORCEINLINE virtual FName GetToolkitFName() const override { return FName("PreviewObjectToolkit"); }
	virtual FText GetBaseToolkitName() const override { return NSLOCTEXT("MyEditor", "PreviewBaseToolkitName", "PreviewBaseToolkitName"); }
	virtual FString GetWorldCentricTabPrefix() const override { return NSLOCTEXT("MyEditor", "PreviewObjectTabPrefix", "PreviewObjectTabPrefix").ToString(); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::Yellow; }

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

	/** End FAssetEditorToolkit Interface */

	void InitializeAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InAssets);

private:

	TObjectPtr<UPreviewObject> EditingPreviewObject = nullptr;
	TSharedPtr<IDetailsView> DetailsViewWidget;

	inline static FName PreviewObjectEditorLayoutName{ "PreviewObjectEditorLayout" };
	inline static FName PreviewObjectEditorDetailTabName{ "PreviewObjectEditorDetailTab" };
	inline static FName PreviewObjectEditorPreviewSceneTabName{ "PreviewObjectEditorPreviewSceneTab" };

	TSharedRef<SDockTab> SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs);
};
