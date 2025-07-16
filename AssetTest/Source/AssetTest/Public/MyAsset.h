// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyAsset.generated.h"

/**
 * 
 */
UCLASS()
class ASSETTEST_API UMyAsset : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyAsset") FName AssetsName;

	UPROPERTY()
	UEdGraph* EdGraph = nullptr;
};
