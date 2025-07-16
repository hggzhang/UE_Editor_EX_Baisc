


#include "FMyGraphSchemaAction_NewNode.h"

UEdGraphNode* FMyGraphSchemaAction_NewNode::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode)
{
    UEdGraphNode* GraphNodeTemplate = Cast<UEdGraphNode>(NodeClass->ClassDefaultObject);
	UEdGraphNode* NewGraphNode = CreateNode(ParentGraph, FromPin, Location, GraphNodeTemplate);

	FScopedTransaction Transaction(NSLOCTEXT("MyEditor", "AddNodeTransaction", "Add Node"));
	const UEdGraphSchema* GraphSchema = ParentGraph->GetSchema();

	if (FromPin)
	{
		for (const auto& Pin : NewGraphNode->Pins)
		{
			if (GraphSchema->TryCreateConnection(FromPin, Pin))
			{
				break;
			}
		}
	}

	ParentGraph->NotifyGraphChanged();

	return NewGraphNode;
}
