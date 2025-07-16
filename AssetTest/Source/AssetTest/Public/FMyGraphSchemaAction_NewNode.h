
#pragma once

#include "CoreMinimal.h"
#include "FMyGraphSchemaAction_NewNode.generated.h"

USTRUCT()
struct FMyGraphSchemaAction_NewNode : public FEdGraphSchemaAction_NewNode
{
	GENERATED_USTRUCT_BODY()
public:

	TObjectPtr<UClass> NodeClass;

	FMyGraphSchemaAction_NewNode()
		: FEdGraphSchemaAction_NewNode(FText::GetEmpty(), FText::GetEmpty(), FText::GetEmpty(), 0)
		, NodeClass(nullptr)
	{
	}

	FMyGraphSchemaAction_NewNode(
		UClass* InNodeClass,
		FText InNodeCategory,
		FText InMenuDesc,
		FText InToolTip,
		const int32 InGrouping)
		: FEdGraphSchemaAction_NewNode(
			InNodeCategory,
			InMenuDesc,
			InToolTip,
			InGrouping
		), NodeClass(InNodeClass) {
	}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;
	
};