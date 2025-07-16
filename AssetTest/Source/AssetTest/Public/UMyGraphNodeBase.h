
#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "UMyGraphNodeBase.generated.h"

UCLASS()
class ASSETTEST_API UMyGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

public:

	UMyGraphNodeBase() {}

	inline static FName MyGraphNodePinCategory{ "MyGraphNodePinCategory" };
	inline static FName MyGraphNodePinSubCategory{ "MyGraphNodePinSubCategory" };


	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;

	FORCEINLINE virtual FText GetNodeDisplayName() const { return NSLOCTEXT("Editor", "NodeDisplayNameBase", "NodeDisplayNameBase"); }

	// Called when the node is selected in the graph editor, Not yet implemented
	void OnNodeSelected() {}
	void OnNodeCancelSelected() {}

};

