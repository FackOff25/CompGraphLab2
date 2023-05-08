// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CEdge.h"
#include "DynamicEdge.generated.h"

/**
 * 
 */
UCLASS()
class LAB2_KOZLOV_API ADynamicEdge : public ACEdge
{
	GENERATED_BODY()

public:
	ADynamicEdge();

	UFUNCTION()
		void UpdateStart(FVector newStart, int instanceId);

	UFUNCTION()
		void UpdateEnd(FVector newEnd, int instanceId);

private:
		void UpdateEdge(int instanceId);
};
