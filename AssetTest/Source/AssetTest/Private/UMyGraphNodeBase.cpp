


#include "UMyGraphNodeBase.h"

void UMyGraphNodeBase::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, MyGraphNodePinCategory, MyGraphNodePinSubCategory, nullptr, TEXT(""));
}

FText UMyGraphNodeBase::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("Editor", "MyGraphNodeBase", "MyGraphNodeBase");
}

FText UMyGraphNodeBase::GetTooltipText() const
{
	return NSLOCTEXT("Editor", "MyGraphNodeTooltipBase", "MyGraphNodeTooltipBase");
}

FLinearColor UMyGraphNodeBase::GetNodeTitleColor() const
{
	return FLinearColor::Red;
}