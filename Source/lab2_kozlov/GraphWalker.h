// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSphere.h"
#include "DynamicEdge.h"
#include "Graph.h"
#include "GraphWalker.generated.h"

/**
 * 
 */
UCLASS()
class LAB2_KOZLOV_API AGraphWalker : public ACSphere
{
	GENERATED_BODY()

public:
	AGraphWalker();

		void SetParams(int _sizeX, int _sizeY, TArray<FVector> graphVertexes, TArray<FCMatrix> _edges, int startId, int endId, int _speed);

		virtual void Tick(float DeltaTime) override;

private:
		bool GetShortestPath(int id, int end, int lenLeft);

		TArray<int> GetPathVertexes();

		void UpdateMovingVector();

		void FindShortestPath(int id1, int id2);

		void DrawPath();

	UPROPERTY()
		float speed = 1;

		int lastVert;

		int nextVert;

		int finishVert;

		FVector destination;

		FVector movingVector;

		int sizeX = 0;

		int sizeY = 0;

		TArray<FVector> graphVertexes;

		TArray<FCMatrix> edges;

		TArray<FVector2D> path;

		ADynamicEdge* edgePath;

		UPROPERTY()
			FLinearColor WalkerColor = { 1,0,1 };

		bool came;

		float WalkerScale = 0.2f;
};
