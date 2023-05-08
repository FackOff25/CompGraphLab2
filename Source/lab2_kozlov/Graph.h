// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Graph.generated.h"

USTRUCT()
struct FCMatrix
{
	GENERATED_BODY()

	TArray<int> arr;
};

UCLASS()
class LAB2_KOZLOV_API AGraph : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGraph();

		void Init(int size_x, int size_y, float _disperse);
		FVector GetVertex(int id);
		FVector GetVertex(int x, int y);
		FVector GetCoords(int id);
		int GetSizeX();
		int GetSizeY();
		TArray<FVector> GetVertexes();
		TArray<FCMatrix> GetEdges();

private:

	UPROPERTY()
		int sizeX = 0;

	UPROPERTY()
		int sizeY = 0;

	UPROPERTY()
		int disperse = 0;

		TArray<FVector> vertexes;
		TArray<FCMatrix> edgeMatrix;
		FLinearColor edgeColor = { 0,0,0 };
		int MakeIDfromCoords(int x, int y);
		void DrawGraph(UWorld* world);
		float GetRandomDisperse(float norm);
		bool IsConnected(int id);
		TArray<int> ChoseOptions(TArray<int> options);
		void GenerateEdges();
		void DrawEdges(UWorld* world);
};


