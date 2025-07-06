// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyAsset2Factory.generated.h"

/**
 * 
 */
UCLASS()
class ASSETTEST_API UMyAsset2Factory : public UFactory
{
	GENERATED_BODY()

public:
	UMyAsset2Factory();

	virtual bool CanCreateNew() const override;
	virtual bool ShouldShowInNewMenu() const override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
