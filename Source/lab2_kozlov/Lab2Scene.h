// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lab2Scene.generated.h"

UCLASS()
class LAB2_KOZLOV_API ALab2Scene : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALab2Scene();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
