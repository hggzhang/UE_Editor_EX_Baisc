


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
	// ������ֻ��Ϊ�������򵥵���ʾ��������ô���ġ�
	// ������Ҫ�༭һ�����Ա��־û��洢��ͼ��ͼӦ�ô����Զ����ʲ��У����Զ�����Ĵ�����ʼ����

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
	//�������Ա༭��ģ��
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs;
	//�������Ա༭����Slate
	const TSharedRef<IDetailsView> AssetPropertyView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	//�������룬���������Զ����ɶ�����������
	AssetPropertyView->SetObject(GetEditingObject());
	return SNew(SDockTab)
		[
			AssetPropertyView
		];
}
