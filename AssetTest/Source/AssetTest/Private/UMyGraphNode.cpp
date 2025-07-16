


#include "UMyGraphNode.h"

FText UMyGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("Editor", "MyGraphNode", "MyGraphNode");
}

FText UMyGraphNode::GetTooltipText() const
{
	return NSLOCTEXT("Editor", "MyGraphNodeTooltip", "MyGraphNodeTooltip");
}