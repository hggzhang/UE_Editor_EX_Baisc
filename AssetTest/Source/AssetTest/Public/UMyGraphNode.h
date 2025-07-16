

#pragma once

#include "CoreMinimal.h"
#include "UMyGraphNodeBase.h"
#include "UMyGraphNode.generated.h"

UCLASS()
class ASSETTEST_API UMyGraphNode : public UMyGraphNodeBase
{
	GENERATED_BODY()

public:

	UMyGraphNode() {}

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;

	FORCEINLINE virtual FText GetNodeDisplayName() const { return NSLOCTEXT("Editor", "MyNodeDisplayName", "MyNodeDisplayName"); }
};
