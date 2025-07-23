

#pragma once

#include "CoreMinimal.h"
#include "UPreviewObjectFactory.generated.h"

UCLASS()
class TESTPREVIEWSCENE_API UPreviewObjectFactory : public UFactory
{
	GENERATED_BODY()

public:

	UPreviewObjectFactory();

	virtual bool CanCreateNew() const override;
	virtual bool ShouldShowInNewMenu() const override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
