

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ASSETTEST_API FMyAssetEditorToolkit : public FAssetEditorToolkit
{
public:
	// ����ʵ�ֵĽӿ�
	virtual FName GetToolkitFName() const override { return FName("MyAssetsEditorToolkit"); }
	virtual FText GetBaseToolkitName() const override { return NSLOCTEXT("EditorExtension", "My Asset Toolkit Name", "�ҵ��ʲ��༭��"); }
	virtual FString GetWorldCentricTabPrefix() const override { return NSLOCTEXT("EditorExtension", "My Asset Toolkit Tab Prefix", "�ҵ��ʲ�").ToString(); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::Green; }

public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	// ��������������麯����Ҳ������ģʽƥ�䣬Ϊ�����������ⲿ����
	void InitializeAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InAssets);

private:

	// ����ϸ�����
	TSharedRef<SDockTab> SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs) const;
	TObjectPtr<UEdGraph> EdGraph;
};
