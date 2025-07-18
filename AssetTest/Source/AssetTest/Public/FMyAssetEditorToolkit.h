

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ASSETTEST_API FMyAssetEditorToolkit : public FAssetEditorToolkit
{
public:
	virtual FName GetToolkitFName() const override { return FName("MyAssetsEditorToolkit"); }
	virtual FText GetBaseToolkitName() const override { return NSLOCTEXT("EditorExtension", "My Asset Toolkit Name", "MyAssetEditor"); }
	virtual FString GetWorldCentricTabPrefix() const override { return NSLOCTEXT("EditorExtension", "My Asset Toolkit Tab Prefix", "MyAsset").ToString(); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::Green; }

public:
	// register and unregister tab spawners for the asset editor
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	// Initializes the asset editor with the provided mode, host, and asset.
	void InitializeAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InAssets);
private:

	TSharedPtr<IDetailsView> DetailsView;
	// Spawns the detail and graph editor tabs for the asset editor
	TSharedRef<SDockTab> SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<SDockTab> SpawnGraphEditorTab(const FSpawnTabArgs& SpawnTabArgs);

private:

	TSharedPtr<SGraphEditor> GraphEditor;
	TSharedPtr<FUICommandList> MyCommandList;
	TSharedPtr<TSet<UObject*>> SelectedNodesLastTime{};

	// Handles node actions in the graph editor
	void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection) const;
	void CopySelectedNodes();
	void DeleteSelectedNode();
	void CutSelectedNodes();
	void DeleteSelectedDuplicatableNodes();
	void PasteNodes();
};
