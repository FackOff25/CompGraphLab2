// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConfigReader.generated.h"

/**
 * 
 */
UCLASS()
class LAB2_KOZLOV_API UConfigReader : public UObject
{
	GENERATED_BODY()

public:
		static TMap<FString, FString> ReadConfig(FString path);
};
