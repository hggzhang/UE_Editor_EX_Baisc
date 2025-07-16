// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetFactory.h"
#include "MyAsset.h"
#include "UMyGraphNode.h"
#include "UMyGraphSchema.h"

UMyAssetFactory::UMyAssetFactory()
{
	SupportedClass = UMyAsset::StaticClass();
	bCreateNew = true;
}

bool UMyAssetFactory::CanCreateNew() const
{
	return true;
}

bool UMyAssetFactory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UMyAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	UMyAsset* NewAsset = NewObject<UMyAsset>(InParent, InClass, InName, Flags);

	//EdGraph* Graph = FBlueprintEditorUtils::CreateNewGraph(NewAsset, InName, UEdGraph::StaticClass(), UMyGraphSchema::StaticClass());

	NewAsset->EdGraph = NewObject<UEdGraph>(NewAsset);
	NewAsset->EdGraph->Schema = UMyGraphSchema::StaticClass();
	NewAsset->EdGraph->AddToRoot();


	UEdGraphNode* EdGraphNode = CreateMyNode(NewAsset->EdGraph, { 0, 0 });
	NewAsset->EdGraph->AddNode(EdGraphNode);

	return NewAsset;
}

UEdGraphNode* UMyAssetFactory::CreateMyNode(UEdGraph* ParentGraph, const FVector2D NodeLocation) const
{
	check(ParentGraph != nullptr)
		UEdGraphNode* ResultGraphNode = NewObject<UMyGraphNode>(ParentGraph);
	ParentGraph->Modify();
	ResultGraphNode->SetFlags(RF_Transactional);

	ResultGraphNode->Rename(nullptr, ParentGraph, REN_NonTransactional);
	ResultGraphNode->CreateNewGuid();
	ResultGraphNode->NodePosX = NodeLocation.X;
	ResultGraphNode->NodePosY = NodeLocation.Y;

	ResultGraphNode->AllocateDefaultPins();
	return ResultGraphNode;
}
