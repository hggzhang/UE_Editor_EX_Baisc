// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */
class ASSETTEST_API FAssetTypeActions_MyAsset : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_MyAsset(EAssetTypeCategories::Type Type);

	virtual FText GetName() const override;

	// Returns the name of the asset type, used in the content browser
	virtual FColor GetTypeColor() const override;
	// Returns the icon for the asset type(MyAsset)
	virtual UClass* GetSupportedClass() const override;
	// Open the asset editor for the asset type(MyAsset)
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	// Returns the category of the asset type(MyAsset)
	virtual uint32 GetCategories() override;
private:
	EAssetTypeCategories::Type MyAssetCategory;
};
