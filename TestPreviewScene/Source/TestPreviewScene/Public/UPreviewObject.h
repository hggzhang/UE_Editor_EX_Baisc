

#pragma once

#include "CoreMinimal.h"
#include "UPreviewObject.generated.h"

DECLARE_DELEGATE(FOnAssetPropertyChanged);

UCLASS()
class TESTPREVIEWSCENE_API UPreviewObject : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ValueFloat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ValueInt;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* StaticMesh;

	FOnAssetPropertyChanged OnAssetPropertyChanged;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
