


#include "FMyAssetEditorToolkit.h"
#include "MyAsset.h"
#include "UMyGraphNode.h"
#include "UMyGraphSchema.h"
#include "Framework/Commands/UICommandList.h"
#include "Framework/Commands/GenericCommands.h"
#include "EdGraphUtilities.h"
#include "Windows/WindowsPlatformApplicationMisc.h"
#include "SNodePanel.h"

void FMyAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	const auto& MenuCategory = TabManager->GetLocalWorkspaceMenuRoot();

	// Register the tabs for the asset editor
	InTabManager->RegisterTabSpawner(FName("MyAssetPropertyTab"), FOnSpawnTab::CreateSP(this, &FMyAssetEditorToolkit::SpawnDetailTab)).SetGroup(MenuCategory);;
	InTabManager->RegisterTabSpawner(FName("MyAssetsGraphEditorTab"), FOnSpawnTab::CreateSP(this, &FMyAssetEditorToolkit::SpawnGraphEditorTab)).SetGroup(MenuCategory);;
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
	UMyAsset* CustomAsset = Cast<UMyAsset>(InAssets);
	if (!CustomAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid asset type provided"));
		return;
	}

	SelectedNodesLastTime = MakeShareable(new TSet<UObject*>);

	// Create the EdGraph if it doesn't exist
	const TSharedRef<FTabManager::FLayout> StandaloneMyAssetEditor = FTabManager::NewLayout("MyAssetEditor")->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(EOrientation::Orient_Horizontal)
		->Split(FTabManager::NewStack()->AddTab(FName("MyAssetsGraphEditorTab"), ETabState::OpenedTab))
		->Split(FTabManager::NewStack()->AddTab(FName("MyAssetPropertyTab"), ETabState::OpenedTab))
	);
	InitAssetEditor(Mode, InitToolkitHost, FName("MyAssetEditor"), StandaloneMyAssetEditor, true, true, InAssets);
	RegenerateMenusAndToolbars();
}

TSharedRef<SDockTab> FMyAssetEditorToolkit::SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs)
{
	// Create the details view for the asset properties
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs;
	const TSharedRef<IDetailsView> AssetPropertyView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	// Set the object to be edited in the details view
	AssetPropertyView->SetObject(GetEditingObject());
	DetailsView = AssetPropertyView;
	return SNew(SDockTab)
		[
			AssetPropertyView
		];
}

TSharedRef<SDockTab> FMyAssetEditorToolkit::SpawnGraphEditorTab(const FSpawnTabArgs& SpawnTabArgs)
{

	UMyAsset* CustomAsset = Cast<UMyAsset>(GetEditingObject());
	auto GraphSchema = CustomAsset->EdGraph->GetSchema();
	auto MyGraphSchema = Cast<UMyGraphSchema>(GraphSchema);

	MyCommandList = MakeShareable(new FUICommandList);
	// Map commands to actions
	MyCommandList->MapAction(FGenericCommands::Get().Delete, FExecuteAction::CreateRaw(this, &FMyAssetEditorToolkit::DeleteSelectedNode));
	MyCommandList->MapAction(FGenericCommands::Get().Copy, FExecuteAction::CreateRaw(this, &FMyAssetEditorToolkit::CopySelectedNodes));
	MyCommandList->MapAction(FGenericCommands::Get().Paste, FExecuteAction::CreateRaw(this, &FMyAssetEditorToolkit::PasteNodes));
	MyCommandList->MapAction(FGenericCommands::Get().Cut, FExecuteAction::CreateRaw(this, &FMyAssetEditorToolkit::CutSelectedNodes));

	// Create the graph editor widget
	SGraphEditor::FGraphEditorEvents GraphEditorEvents;
	GraphEditorEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FMyAssetEditorToolkit::OnSelectedNodesChanged);

	// Set up the graph appearance info
	FGraphAppearanceInfo GraphAppearanceInfo;
	GraphAppearanceInfo.CornerText = NSLOCTEXT("Editor", "MyAppearance", "MyTestGragh");

	GraphEditor = SNew(SGraphEditor)
		.GraphToEdit(CustomAsset->EdGraph)
		.AdditionalCommands(MyCommandList)
		.GraphEvents(GraphEditorEvents)
		.Appearance(GraphAppearanceInfo);

	return SNew(SDockTab)
		[
			GraphEditor.ToSharedRef()
		];
}

void FMyAssetEditorToolkit::DeleteSelectedNode()
{
	if (!GraphEditor.IsValid())
	{
		return;
	}

	// resource acquisition is initialization (RAII) pattern to ensure the transaction is scoped
	const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());

	// Modify the graph
	GraphEditor->GetCurrentGraph()->Modify();

	const FGraphPanelSelectionSet SelectedNodes = GraphEditor->GetSelectedNodes();
	GraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator NodeIterator(SelectedNodes); NodeIterator; ++NodeIterator)
	{
		if (UEdGraphNode* GraphNodeToDelete = Cast<UEdGraphNode>(*NodeIterator))
		{
			if (GraphNodeToDelete->CanUserDeleteNode())
			{
				GraphNodeToDelete->Modify();
				GraphNodeToDelete->DestroyNode();
			}
		}
	}
}

void FMyAssetEditorToolkit::CopySelectedNodes()
{
	const FGraphPanelSelectionSet SelectedNodes = GraphEditor->GetSelectedNodes();

	FString ExportedText;

	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		if (UMyGraphNode* Node = Cast<UMyGraphNode>(*SelectedIter))
		{
			Node->PrepareForCopying();
		}
	}

	// Export the selected nodes to text
	FEdGraphUtilities::ExportNodesToText(SelectedNodes, ExportedText);
	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);
}

void FMyAssetEditorToolkit::CutSelectedNodes()
{
	CopySelectedNodes();
	DeleteSelectedDuplicatableNodes();
}

void FMyAssetEditorToolkit::PasteNodes()
{
	const FVector2D Location{ GraphEditor->GetPasteLocation() };
	const FScopedTransaction Transaction(NSLOCTEXT("Editor", "PasteNode", "PasteNode"));

	GraphEditor->GetCurrentGraph()->Modify();
	GraphEditor->ClearSelectionSet();

	// Get the text from the clipboard
	FString TextToImport;
	FPlatformApplicationMisc::ClipboardPaste(TextToImport);

	TSet<UEdGraphNode*> PastedNodes;
	FEdGraphUtilities::ImportNodesFromText(GraphEditor->GetCurrentGraph(), TextToImport, PastedNodes);

	// Culate the average position of the pasted nodes
	FVector2D AvgNodePosition(0.0f, 0.0f);

	for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
	{
		const UEdGraphNode* Node = *It;
		AvgNodePosition.X += Node->NodePosX;
		AvgNodePosition.Y += Node->NodePosY;
	}

	if (PastedNodes.Num() > 0)
	{
		const float InvNumNodes = 1.0f / static_cast<float>(PastedNodes.Num());
		AvgNodePosition.X *= InvNumNodes;
		AvgNodePosition.Y *= InvNumNodes;
	}

	// Adjust the position of the pasted nodes
	for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
	{
		UEdGraphNode* Node = *It;

		GraphEditor->SetNodeSelection(Node, true);

		Node->NodePosX = (Node->NodePosX - AvgNodePosition.X) + Location.X;
		Node->NodePosY = (Node->NodePosY - AvgNodePosition.Y) + Location.Y;

		Node->SnapToGrid(SNodePanel::GetSnapGridSize());

		Node->CreateNewGuid();
	}

	// Notify the graph editor that the graph has changed
	GraphEditor->NotifyGraphChanged();

	// Refresh the graph editor
	GetEditingObject()->PostEditChange();
	GetEditingObject()->MarkPackageDirty();
}

void FMyAssetEditorToolkit::DeleteSelectedDuplicatableNodes()
{
	const FGraphPanelSelectionSet OldSelectedNodes = GraphEditor->GetSelectedNodes();

	FGraphPanelSelectionSet RemainingNodes;
	GraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(OldSelectedNodes); SelectedIter; ++SelectedIter)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter); (Node != nullptr) && Node->CanDuplicateNode())
		{
			GraphEditor->SetNodeSelection(Node, true);
		}
		else
		{
			RemainingNodes.Add(Node);
		}
	}

	DeleteSelectedNode();

	GraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(RemainingNodes); SelectedIter; ++SelectedIter)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter))
		{
			GraphEditor->SetNodeSelection(Node, true);
		}
	}
}

void FMyAssetEditorToolkit::OnSelectedNodesChanged(const TSet<UObject*>& NewSelection) const
{
	TArray<UObject*> Selection;

	const TSet<UObject*> OldSelected = *SelectedNodesLastTime;

	TSet<UObject*> NewSelectedNodes = NewSelection.Difference(OldSelected);
	TSet<UObject*> CancelSelectedNodes = OldSelected.Difference(NewSelection);

	for (UObject* NewSelectedNode : NewSelectedNodes)
	{
		if (UMyGraphNodeBase* Node = CastChecked<UMyGraphNodeBase>(NewSelectedNode))
		{
			Node->OnNodeSelected();
		}
	}

	for (UObject* CancelSelectedNode : CancelSelectedNodes)
	{
		if (UMyGraphNodeBase* Node = CastChecked<UMyGraphNodeBase>(CancelSelectedNode))
		{
			Node->OnNodeCancelSelected();
		}
	}

	SelectedNodesLastTime->Empty();
	SelectedNodesLastTime->Append(NewSelection);

	for (UObject* SelectionEntry : NewSelection)
	{
		Selection.Add(SelectionEntry);
	}
	if (Selection.Num() == 0)
	{
		DetailsView->SetObject(GetEditingObject());
	}
	else
	{
		DetailsView->SetObjects(Selection);
	}
}
