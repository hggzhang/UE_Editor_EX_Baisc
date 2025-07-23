

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class TESTPREVIEWSCENE_API FAssetTypeActions_PreviewObject : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_PreviewObject(EAssetTypeCategories::Type Type);
	/** Begin FAssetTypeActions_Base Interface */
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;
	virtual FColor GetTypeColor() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;

private:
	EAssetTypeCategories::Type TypeCategories;
};
