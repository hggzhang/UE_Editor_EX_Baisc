


#include "UMyInOutGraphNode.h"

FText UMyInOutGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("Editor", "MyGraphNodeInOut", "MyGraphNodeInOut");
}

FText UMyInOutGraphNode::GetTooltipText() const
{
	return NSLOCTEXT("Editor", "MyGraphNodeTooltipInOut", "MyGraphNodeTooltipInOut");
}

void UMyInOutGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, MyGraphNodePinCategory, MyGraphNodePinSubCategory, nullptr, TEXT("In"));
	CreatePin(EGPD_Output, MyGraphNodePinCategory, MyGraphNodePinSubCategory, nullptr, TEXT("Out"));
}