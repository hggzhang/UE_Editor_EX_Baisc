

#pragma once

#include "CoreMinimal.h"
#include "UMyGraphNodeBase.h"
#include "UMyInOutGraphNode.generated.h"

UCLASS()
class ASSETTEST_API UMyInOutGraphNode : public UMyGraphNodeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Value;

	UMyInOutGraphNode() {}

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;

	FORCEINLINE virtual FText GetNodeDisplayName() const { return NSLOCTEXT("Editor", "MyNodeInOutDisplayName", "MyNodeInOutDisplayName"); }
};
