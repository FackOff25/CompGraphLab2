// Fill out your copyright notice in the Description page of Project Settings.

#include "Graph.h"
#include "Dot.h"
#include "CEdge.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AGraph::AGraph()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorLocation(FVector(0, 0, 0));
}

void AGraph::Init(int size_x, int size_y, float _disperse) {
	sizeX = size_x;
	sizeY = size_y;
	disperse = _disperse;
	for (int i = 0; i < sizeX * sizeY; ++i) {
		FCMatrix line;
		line.arr.AddZeroed(sizeX * sizeY);
		edgeMatrix.Add(line);
	}
	DrawGraph(GetWorld());
}

float AGraph::GetRandomDisperse(float norm) {
	return FMath::FRandRange(- norm/2, norm/2);
}

void AGraph::DrawGraph(UWorld* world) {
	float edgeLen = 50;
	float xMove = (sizeX / 2.0f) * edgeLen;
	float yMove = (sizeY / 2.0f) * edgeLen;
	vertexes.AddUninitialized(sizeX * sizeY);
	ADot* dot = world->SpawnActor<ADot>();
	dot->Init(FVector(0,0,0));
	for (int i = 0; i < sizeX; ++i) {
		for (int j = 0; j < sizeY; ++j) {
			FVector newCoords((i + 1) * edgeLen + GetRandomDisperse(disperse) - xMove, (j+1)*edgeLen + GetRandomDisperse(disperse) - yMove, 0);
			vertexes[MakeIDfromCoords(i, j)] = newCoords;
			dot->AddNewInstance(newCoords);
		}
	}

	GenerateEdges();
	DrawEdges(world);
}

void AGraph::DrawEdges(UWorld* world) {
	ACEdge* edge = world->SpawnActor<ACEdge>();
	for (int i = 0; i < sizeX * sizeY; ++i) {
		for (int j = i + 1; j < sizeX * sizeY; ++j) {
			if (edgeMatrix[i].arr[j]) {
				edge->DrawStaticEdge(GetVertex(i), GetVertex(j), edgeColor);
			}
		}
	}
}

int AGraph::MakeIDfromCoords(int x, int y) {
	return y * sizeX + x;
}

FVector AGraph::GetVertex(int id) {
	return vertexes[id];
}

FVector AGraph::GetVertex(int x, int y) {
	return vertexes[MakeIDfromCoords(x, y)];
}

FVector AGraph::GetCoords(int id) {
	int x = id % sizeX;
	int y = (id - x) / sizeX;
	return FVector(x, y, 0);
}

//Gets vector of zero and 1; Randomly make non-zero ones zero, returns result
TArray<int> AGraph::ChoseOptions(TArray<int> options) {
	TArray<int> buf = options;
	for (int i = 0; i < options.Num(); ++i) {
		if (buf[i] != 0) {
			buf[i] = FMath::RandRange(0, 1);
		}
	}
	return buf;
}

bool AGraph::IsConnected(int id) {
	return edgeMatrix[id].arr.Contains(1);
}

void AGraph::GenerateEdges() {
	edgeMatrix.Reset();
	for (int i = 0; i < sizeX * sizeY; ++i) {
		FCMatrix line;
		line.arr.AddZeroed(sizeX * sizeY);
		edgeMatrix.Add(line);
	}

	int id1, id2;
	FVector2D edge;
	for (int i = 0; i < sizeX - 1; ++i) {
		id1 = i;
		id2 = i + 1;
		edge = FVector2D(id1, id2);
		edgeMatrix[id1].arr[id2] = 1;
		edgeMatrix[id2].arr[id1] = 1;
	}

	TArray<int> options1 = { 0, 1, 1, 1 };
	TArray<int> options2 = { 1, 1, 0, 1 };

	for (int j = 0; j < sizeY; ++j) {
		for (int i = 0; i < sizeX; ++i) {
			TArray<int> buf;
			id1 = MakeIDfromCoords(i, j);
			if (!IsConnected(id1)) {
				id2 = id1 - sizeX;
				edge = FVector2D(id2, id1);
				edgeMatrix[id1].arr[id2] = 1;
				edgeMatrix[id2].arr[id1] = 1;
			};
			if (j % 2 == 0) {
				buf = options1;
				if (j == sizeY - 1) {
					buf[1] = 0;
					buf[2] = 0;
				}
				if (i == sizeX - 1) {
					buf[2] = 0;
					buf[3] = 0;
				}
			}
			else {
				buf = options2;
				if (j == sizeY - 1) {
					buf[0] = 0;
					buf[1] = 0;
				}
				if (i == sizeX - 1) {
					buf[3] = 0;
				}

				if (i == 0) {
					buf[0] = 0;
				}
			}
			
			buf = ChoseOptions(buf);

			if (buf[0] == 1) {
				id2 = MakeIDfromCoords(i - 1, j + 1);
				edge = FVector2D(id1, id2);
				edgeMatrix[id1].arr[id2] = 1;
				edgeMatrix[id2].arr[id1] = 1;
			}
			if (buf[1] == 1) {
				id2 = MakeIDfromCoords(i, j + 1);
				edge = FVector2D(id1, id2);
				edgeMatrix[id1].arr[id2] = 1;
				edgeMatrix[id2].arr[id1] = 1;
			}
			if (buf[2] == 1) {
				id2 = MakeIDfromCoords(i + 1, j + 1);
				edge = FVector2D(id1, id2);
				edgeMatrix[id1].arr[id2] = 1;
				edgeMatrix[id2].arr[id1] = 1;
			}
			if (buf[3] == 1) {
				id2 = MakeIDfromCoords(i + 1, j);
				edge = FVector2D(id1, id2);
				edgeMatrix[id1].arr[id2] = 1;
				edgeMatrix[id2].arr[id1] = 1;
			}
		}
	}
}

int AGraph::GetSizeX() {
	return sizeX;
};

int AGraph::GetSizeY() {
	return sizeY;
};

TArray<FVector> AGraph::GetVertexes() {
	return vertexes;
}

TArray<FCMatrix> AGraph::GetEdges() {
	return edgeMatrix;
}
