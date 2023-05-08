// Fill out your copyright notice in the Description page of Project Settings.


#include "CEdge.h"

// Sets default values
ACEdge::ACEdge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(GetRootComponent());
	Mesh->NumCustomDataFloats = 3;

	UpdateMaterial(MaterialReference);

	const TCHAR* CMeshPath = *MeshReference;
	ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMeshAsset(CMeshPath);

	if (BaseMeshAsset.Object)
	{
		Mesh->SetStaticMesh(BaseMeshAsset.Object);
	}
}

void ACEdge::UpdateMaterial(FString reference) {
	const TCHAR* CMaterialPath = *reference;
	ConstructorHelpers::FObjectFinder<UMaterial> BaseMaterialAsset(CMaterialPath);

	if (BaseMaterialAsset.Object)
	{
		Material = (UMaterial*)BaseMaterialAsset.Object;

		Mesh->SetMaterial(0, Material);
	}
};

void ACEdge::SetStart(FVector _start) {
	start = _start;
}

void ACEdge::SetEnd(FVector _end) {
	end = _end;
}

void ACEdge::SetColor(FLinearColor _color) {
	color = _color;
}

void ACEdge::UpdateColor(FLinearColor _color) {
	TArray<float> customData;
	customData.Reserve(3);

	customData.Add(_color.R);
	customData.Add(_color.G);
	customData.Add(_color.B);

	Mesh->SetCustomData(Mesh->GetInstanceCount() - 1, customData, false);
}

int ACEdge::DrawStaticEdge(FVector _start, FVector _end, FLinearColor _color) {
	SetStart(_start);
	SetEnd(_end);
	SetColor(_color);
	return DrawStaticEdge();
}

int ACEdge::DrawStaticEdge(FLinearColor _color) {
	SetColor(_color);
	return DrawStaticEdge();
}

int ACEdge::DrawStaticEdge() {

	FVector edgeVector = end - start;
	FRotator rotation = edgeVector.Rotation();
	rotation.Pitch = 90;
	rotation.Roll += 180;
	FVector transform(height, height, edgeVector.Size() / 100);

	Mesh->AddInstance(FTransform(rotation, start, transform));

	FEdgeInfo edgeInfo;
	edgeInfo.start = start;
	edgeInfo.end = end;
	edgeInfo.color = color;
	edgeInfo.height = height;
	instanceInfo.Add(edgeInfo);

	UpdateColor(color);
	return Mesh->GetInstanceCount();
}

void ACEdge::DestroyEdge(int instanceId) {
	Mesh->RemoveInstance(instanceId);
	instanceInfo.RemoveAt(instanceId);
}

