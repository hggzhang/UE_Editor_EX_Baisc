// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAsset2Factory.h"
#include "MyAsset2.h"


UMyAsset2Factory::UMyAsset2Factory()
{
	SupportedClass = UMyAsset2::StaticClass();
	bCreateNew = true;
}

bool UMyAsset2Factory::CanCreateNew() const
{
	return true;
}

bool UMyAsset2Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UMyAsset2Factory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UMyAsset2>(InParent, InClass, InName, Flags);
}
