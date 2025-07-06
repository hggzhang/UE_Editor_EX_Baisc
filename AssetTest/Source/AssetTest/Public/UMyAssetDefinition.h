

#pragma once

#include "AssetDefinitionDefault.h"
#include "MyAsset2.h"
#include "UMyAssetDefinition.generated.h"

UCLASS()
class ASSETTEST_API UMyAssetDefinition : public UAssetDefinitionDefault
{
	GENERATED_BODY()

public:
	UMyAssetDefinition() 
    {
        IncludeClassInFilter = EIncludeClassInFilter::Always;
    };

    // 必须实现的基本方法
    virtual FText GetAssetDisplayName() const override { return NSLOCTEXT("Editor", "MyAssets", "MyAsset2"); }
    virtual FLinearColor GetAssetColor() const override { return FLinearColor::Green; }
    virtual TSoftClassPtr<UObject> GetAssetClass() const override { return UMyAsset2::StaticClass(); }
    ;
    //virtual bool CanRegisterStatically() const { return true; }
    virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override
    {
        static const TArray<FAssetCategoryPath> Categories = {
            EAssetCategoryPaths::Basic,
            EAssetCategoryPaths::Gameplay
        };
        return Categories;
    }
};
