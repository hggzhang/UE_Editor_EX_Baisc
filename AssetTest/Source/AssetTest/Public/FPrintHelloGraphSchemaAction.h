#pragma once

#include "CoreMinimal.h"
#include "FPrintHelloGraphSchemaAction.generated.h"

USTRUCT()
struct FPrintHelloGraphSchemaAction : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY()

public:

	FPrintHelloGraphSchemaAction() : FEdGraphSchemaAction(
		NSLOCTEXT("Editor", "Actions Category", "MyActionsMenu"),
		NSLOCTEXT("Editor", "Print Hello Action", "Print Hello Action"),
		NSLOCTEXT("Editor", "Print Hello Tooltip", "Print Hello Tooltip"),
		0
	) {
	}

	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) override
	{
		if (FromPin)
		{
			FMessageDialog::Open(EAppMsgType::Ok, NSLOCTEXT("EditorExtension", "Print Action With Pin", "Hello World With Pin"));
		}
		else
		{
			FMessageDialog::Open(EAppMsgType::Ok, NSLOCTEXT("EditorExtension", "Print Action Without Pin", "Hello World Without Pin"));
		}
		return nullptr;
	}
};