// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSphere.h"
#include "Dot.generated.h"

/**
 * 
 */
UCLASS()
class LAB2_KOZLOV_API ADot : public ACSphere
{
	GENERATED_BODY()
	
public:
		ADot();
private:
	UPROPERTY()
		float DotScale = 0.1f;

	UPROPERTY()
		FLinearColor DotColor = {1,1,0};
};
