// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphWalker.h"

AGraphWalker::AGraphWalker() {
	PrimaryActorTick.bCanEverTick = true;
	scale = WalkerScale;
	color = WalkerColor;
}

void AGraphWalker::SetParams(int _sizeX, int _sizeY, TArray<FVector> _graphVertexes, TArray<FCMatrix> _edges, int startId, int endId, int _speed) {
	sizeX = _sizeX;
	sizeY = _sizeY;
	graphVertexes = _graphVertexes;
	edges = _edges;
	lastVert = startId;
	finishVert = endId;
	speed = _speed;
	came = false;
	edgePath = GetWorld()->SpawnActor<ADynamicEdge>();

	Init(graphVertexes[lastVert]);
	AddNewInstance();
	UpdateMovingVector();
	DrawPath();
};

TArray<int> AGraphWalker::GetPathVertexes() {
	TArray<int> vertexes;
	for (FVector2D edge : path) {
		if (!vertexes.Contains(edge[0])) {
			vertexes.Add(edge[0]);
			continue;
		}
		if (!vertexes.Contains(edge[1])) {
			vertexes.Add(edge[1]);
		}
	}
	return vertexes;
};

bool AGraphWalker::GetShortestPath(int id, int end, int lenLeft) {
	if (lenLeft == 0) {
		if (id == end) {
			return true;
		}
		return false;
	}
	TArray<int> pathVertexes = GetPathVertexes();
	TArray<FVector2D> edgesOfStart;
	for (int i = 0; i < sizeX * sizeY; ++i) {
		if (edges[id].arr[i] == 1) {
			path.Push(FVector2D(id, i));
			pathVertexes.Push(i);
			if (GetShortestPath(i, end, lenLeft - 1)) {
				return true;
			};
			path.Pop();
			pathVertexes.Pop();
		}
	}
	return false;
};

void AGraphWalker::FindShortestPath(int start, int end) {
	path.Reset();

	TArray<int> visited, queue;
	TMap<int, int> shortestPathTo;

	queue.Push(start);
	shortestPathTo.Add(start, 0);

	while (queue.Num() != 0) {
		int id = queue[0];
		queue.RemoveAt(0);
		int pathToLinked = *shortestPathTo.Find(id);
		++pathToLinked;
		for (int i = 0; i < sizeX * sizeY; ++i) {
			if (edges[id].arr[i] == 1) {
				int* len = shortestPathTo.Find(i);
				if (len == nullptr || *len > pathToLinked) {
					shortestPathTo.Remove(i);
					shortestPathTo.Add(i, pathToLinked);
				}
				if (!(queue.Contains(i) || visited.Contains(i))) {
					queue.Push(i);
				}
			}
		}
		visited.Add(id);
	}

	GetShortestPath(start, end, *shortestPathTo.Find(end));
}

void AGraphWalker::UpdateMovingVector() {
	FindShortestPath(lastVert, finishVert);
	FVector start = graphVertexes[lastVert];
	FVector2D edge = path[0];
	FVector end;
	if (edge[0] == lastVert) {
		nextVert = edge[1];
	}
	else {
		nextVert = edge[0];
	}

	end = graphVertexes[nextVert];
	destination = end;
	movingVector = end - start;
	movingVector = movingVector.GetSafeNormal() * speed;
}

void AGraphWalker::DrawPath() {
	FLinearColor red = { 1,0,0,1 };
	FLinearColor green = { 0,1,0,1 };
	FLinearColor blue = { 0,0,1,1 };
	TArray<FLinearColor> colors = { red, green, blue };
	int colId = 0;
	for (FVector2D edge : path) {
		edgePath->DrawStaticEdge(graphVertexes[edge[0]], graphVertexes[edge[1]], colors[colId]);
		colId = (colId + 1) % 3;
	}
}

void AGraphWalker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (came)
	{
		lastVert = finishVert;
		finishVert = FMath::RandRange(0, sizeX * sizeY - 1);
		if (finishVert == lastVert)
		{
			finishVert = (finishVert + 1) % (sizeX * sizeY);
		}

		position = graphVertexes[lastVert];
		MoveToPosition();

		UpdateMovingVector();
		DrawPath();
		came = false;
	}
	
	MoveRelative(movingVector);

	edgePath->UpdateStart(GetActorLocation(), 0);

	float distance = FVector::DistSquared(GetActorLocation(), destination);

	FVector vectorToDestination = destination - GetActorLocation();

	if (distance <= movingVector.Size() //left one Tick
		|| (vectorToDestination + movingVector).Size() <= movingVector.Size()
		|| (vectorToDestination + movingVector).Size() <= vectorToDestination.Size()) //already passed destination
	{
		lastVert = nextVert;
		if (lastVert == finishVert) {
			came = true;
		}
		else {
			path.RemoveAt(0);
			UpdateMovingVector();
		}
		ADynamicEdge* toDestroy = edgePath;
		toDestroy->DestroyEdge(0);
	}

	Mesh->MarkRenderStateDirty();
}
