// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class ASSETTEST_API UMyAssetFactory : public UFactory
{
	GENERATED_BODY()
	
	UMyAssetFactory();

	virtual bool CanCreateNew() const override;
	virtual bool ShouldShowInNewMenu() const override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
	// Creates a debug node in the specified parent graph at the given location.
	UEdGraphNode* CreateMyNode(UEdGraph* ParentGraph, const FVector2D NodeLocation) const;
};
