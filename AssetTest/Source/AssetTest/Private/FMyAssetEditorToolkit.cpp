


#include "FMyAssetEditorToolkit.h"

void FMyAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	const auto& MenuCategory = TabManager->GetLocalWorkspaceMenuRoot();

	InTabManager->RegisterTabSpawner(FName("MyAssetPropertyTab"), FOnSpawnTab::CreateRaw(this, &FMyAssetEditorToolkit::SpawnDetailTab)).SetGroup(MenuCategory);;
	InTabManager->RegisterTabSpawner(FName("MyAssetsGraphEditorTab"), FOnSpawnTab::CreateLambda([&](const FSpawnTabArgs& SpawnTabArgs)
		{
			return SNew(SDockTab)
				[
					SNew(SGraphEditor).GraphToEdit(EdGraph)
				];
		})).SetGroup(MenuCategory);
}

void FMyAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(FName("MyAssetPropertyTab"));
	InTabManager->UnregisterTabSpawner(FName("MyAssetsGraphEditorTab"));
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

void FMyAssetEditorToolkit::InitializeAssetEditor(const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InAssets)
{
	// 这里我只是为了让他简单的显示出来才这么做的。
	// 如果真的要编辑一个可以被持久化存储的图，图应该存在自定义资产中，随自定义产的创建初始化。

	EdGraph = NewObject<UEdGraph>();
	EdGraph->Schema = UEdGraphSchema::StaticClass();
	EdGraph->AddToRoot();

	const TSharedRef<FTabManager::FLayout> StandaloneMyAssetEditor = FTabManager::NewLayout("MyAssetEditor")->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(EOrientation::Orient_Horizontal)
		->Split(FTabManager::NewStack()->AddTab(FName("MyAssetsGraphEditorTab"), ETabState::OpenedTab))
	);
	InitAssetEditor(Mode, InitToolkitHost, FName("MyAssetEditor"), StandaloneMyAssetEditor, true, true, InAssets);
	RegenerateMenusAndToolbars();
}

TSharedRef<SDockTab> FMyAssetEditorToolkit::SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs) const
{
	//加载属性编辑器模块
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs;
	//创建属性编辑器的Slate
	const TSharedRef<IDetailsView> AssetPropertyView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	//将对象传入，这样就是自动生成对象的属性面板
	AssetPropertyView->SetObject(GetEditingObject());
	return SNew(SDockTab)
		[
			AssetPropertyView
		];
}
