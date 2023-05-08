// Fill out your copyright notice in the Description page of Project Settings.


#include "CSphere.h"

// Sets default values
ACSphere::ACSphere()
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

void ACSphere::SetScale(float newScale) {
	Mesh->SetWorldScale3D(FVector(newScale * 1.0f, newScale * 1.0f, newScale * 1.0f));
};

void ACSphere::SetColor(FLinearColor _color) {
	color = _color;
}

void ACSphere::UpdateColor(FLinearColor _color) {
	TArray<float> customData;
	customData.Reserve(3);

	customData.Add(_color.R);
	customData.Add(_color.G);
	customData.Add(_color.B);

	Mesh->SetCustomData(Mesh->GetInstanceCount() - 1, customData, false);
}


void ACSphere::UpdateMaterial(FString reference) {
	const TCHAR* CMaterialPath = *reference;
	ConstructorHelpers::FObjectFinder<UMaterial> BaseMaterialAsset(CMaterialPath);

	if (BaseMaterialAsset.Object)
	{
		Material = (UMaterial*)BaseMaterialAsset.Object;

		Mesh->SetMaterial(0, Material);
	}
};

bool ACSphere::SetPosition(float x, float y, float z) {
	position = FVector(x, y, z);
	return true;
};

bool ACSphere::SetPosition(FVector vector) {
	return SetPosition(vector[0], vector[1], vector[2]);
};

void ACSphere::MoveAbsolute(FVector vector) {
	SetActorLocation(vector);
};

void ACSphere::MoveRelative(FVector vector) {
	position = GetActorLocation();

	position += vector;

	MoveToPosition();
};

void ACSphere::MoveToPosition() {
	MoveAbsolute(position);
};

void ACSphere::Init(FVector point)
{
	SetScale(scale);
	SetPosition(point);

	MoveToPosition();
	UpdateColor(color);
}

void ACSphere::AddNewInstance()
{
	Mesh->AddInstance(FTransform());
	UpdateColor(color);
}

void ACSphere::AddNewInstance(FVector point)
{
	Mesh->AddInstance(FTransform(point * 10));
	UpdateColor(color);
}
