// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetFactory.h"
#include "MyAsset.h"


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
	return NewObject<UMyAsset>(InParent, InClass, InName, Flags);
}
