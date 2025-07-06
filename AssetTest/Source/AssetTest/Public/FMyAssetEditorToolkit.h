

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ASSETTEST_API FMyAssetEditorToolkit : public FAssetEditorToolkit
{
public:
	// 必须实现的接口
	virtual FName GetToolkitFName() const override { return FName("MyAssetsEditorToolkit"); }
	virtual FText GetBaseToolkitName() const override { return NSLOCTEXT("EditorExtension", "My Asset Toolkit Name", "我的资产编辑器"); }
	virtual FString GetWorldCentricTabPrefix() const override { return NSLOCTEXT("EditorExtension", "My Asset Toolkit Tab Prefix", "我的资产").ToString(); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::Green; }

public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	// 这个函数并不是虚函数，也不含有模式匹配，为公开函数被外部调用
	void InitializeAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InAssets);

private:

	// 生成细节面板
	TSharedRef<SDockTab> SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs) const;
	TObjectPtr<UEdGraph> EdGraph;
};
