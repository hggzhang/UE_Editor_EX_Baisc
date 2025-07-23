


#include "FPreviewObjectEditorToolkit.h"
#include "SPreviewObjectViewPort.h"
#include "FPreviewObjectEditorViewportClient.h"

void FPreviewObjectEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	
	InTabManager->RegisterTabSpawner(PreviewObjectEditorPreviewSceneTabName, FOnSpawnTab::CreateLambda([&](const FSpawnTabArgs& SpawnTabArgs)
		{
			return SNew(SDockTab)
				[
					SNew(SPreviewObjectViewPort).ManagedPreviewObject(EditingPreviewObject)
				];
		}));
	InTabManager->RegisterTabSpawner(PreviewObjectEditorDetailTabName, FOnSpawnTab::CreateRaw(this, &FPreviewObjectEditorToolkit::SpawnDetailTab));
}

void FPreviewObjectEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(PreviewObjectEditorPreviewSceneTabName);
	InTabManager->UnregisterTabSpawner(PreviewObjectEditorDetailTabName);
}

void FPreviewObjectEditorToolkit::InitializeAssetEditor(const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InAssets)
{
	const TSharedRef<FTabManager::FLayout> StandaloneLayout = FTabManager::NewLayout(PreviewObjectEditorLayoutName)->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(EOrientation::Orient_Horizontal)
		->Split
		(
			FTabManager::NewStack()->AddTab(PreviewObjectEditorPreviewSceneTabName, ETabState::OpenedTab)
		)
		->Split
		(
			FTabManager::NewStack()->AddTab(PreviewObjectEditorDetailTabName, ETabState::OpenedTab)
		)
	);

	EditingPreviewObject = Cast<UPreviewObject>(InAssets);
	InitAssetEditor(Mode, InitToolkitHost, FName("PreviewObjectEditor"), StandaloneLayout, true, true, InAssets);
	RegenerateMenusAndToolbars();
}

TSharedRef<SDockTab> FPreviewObjectEditorToolkit::SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs;

	DetailsViewWidget = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsViewWidget->SetObject(GetEditingObject());

	return SNew(SDockTab)
		[
			DetailsViewWidget.ToSharedRef()
		];
}
