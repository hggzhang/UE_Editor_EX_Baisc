

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "UMyGraphSchema.generated.h"

UCLASS()
class ASSETTEST_API UMyGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

protected:
	inline static FName OurNodeContextMenuSection{ "MyNodeContextMenuSection" };
	inline static FName OurPinContextMenuSection{ "MyPinContextMenuSection" };

public:

	UMyGraphSchema() {};

	// This function is called to populate the context menu for the graph
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	// This function is called to populate the context menu for nodes and pins
	virtual void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT("OK!"));
	}
};
