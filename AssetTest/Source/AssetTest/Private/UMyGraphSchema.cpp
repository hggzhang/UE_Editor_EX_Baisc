


#include "UMyGraphSchema.h"
#include "ToolMenus.h"
#include "GraphEditorActions.h"
#include "Framework/Commands/GenericCommands.h"
#include "UMyGraphNode.h"
#include "FPrintHelloGraphSchemaAction.h"
#include "FMyGraphSchemaAction_NewNode.h"
#include "UMyInOutGraphNode.h"
#include "UMyGraphNodeBase.h"

// This function is called to populate the context menu for the graph
void UMyGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	// add a specialized​ action to print "Hello World" when clicked
	const TSharedPtr<FPrintHelloGraphSchemaAction> Action = MakeShareable(new FPrintHelloGraphSchemaAction);
	ContextMenuBuilder.AddAction(Action);

	const UClass* BaseNodeClass = UMyGraphNodeBase::StaticClass();
	TArray<UClass*> NodeClasses;
	GetDerivedClasses(BaseNodeClass, NodeClasses);

	// add all the node classes that derive from UMyGraphNodeBase to the context menu
	for (const auto& NodeClassIterator : NodeClasses){
		const UMyGraphNodeBase* NodeCDO = Cast<UMyGraphNodeBase>(NodeClassIterator->ClassDefaultObject);

		const TSharedPtr<FMyGraphSchemaAction_NewNode> CreateNodeAction = MakeShareable(
			new FMyGraphSchemaAction_NewNode(
				NodeClassIterator,
				NSLOCTEXT("Edition", "MyCreateNodeCategory", "MyCreateNodeCategory"),
				NodeCDO->GetNodeDisplayName(),
				FText::GetEmpty(),
				0
			));
			
		ContextMenuBuilder.AddAction(CreateNodeAction);
	}

	Super::GetGraphContextActions(ContextMenuBuilder);
}

// This function is called to populate the context menu for nodes and pins
void UMyGraphSchema::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	// Register the context menu sections for nodes and pins
	if (Context->Node)
	{
		FToolMenuSection& Section = Menu->AddSection(OurNodeContextMenuSection, NSLOCTEXT("Editor", "MyNodeActions", "MyNodeActions"));
		Section.AddMenuEntry(FGenericCommands::Get().Copy);
		Section.AddMenuEntry(FGenericCommands::Get().Cut);
		Section.AddMenuEntry(FGenericCommands::Get().Paste);
		Section.AddMenuEntry(FGenericCommands::Get().Delete);
	}
	if (Context->Pin)
	{
		FToolMenuSection& Section = Menu->AddSection(OurPinContextMenuSection, NSLOCTEXT("Editor", "MyPinActions", "MyPinActions"));
		Section.AddMenuEntry(FGenericCommands::Get().Delete);
	}
	Super::GetContextMenuActions(Menu, Context);
}





