// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEdge.generated.h"

USTRUCT()
struct FEdgeInfo {
	GENERATED_BODY()

	FVector start;
	FVector end;
	FLinearColor color;
	float height = 0.01;
};

UCLASS()
class LAB2_KOZLOV_API ACEdge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEdge();

		void UpdateMaterial(FString reference);

		void SetStart(FVector _start);

		void SetEnd(FVector _end);

		void SetColor(FLinearColor _color);

		void UpdateColor(FLinearColor _color);

		int DrawStaticEdge(FVector start, FVector finish, FLinearColor color);
		int DrawStaticEdge(FLinearColor color);
		int DrawStaticEdge();

		void DestroyEdge(int instanceId);

protected:
		UInstancedStaticMeshComponent* Mesh;

		UMaterial* Material;

		FVector start;

		FVector end;

		TArray<FEdgeInfo> instanceInfo;

		float height = 0.01;

		float level = 0;

private:
		FLinearColor color;

		FString MeshReference = "StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'";
		FString MaterialReference = "Material'/Game/StarterContent/Materials/M_Colorized.M_Colorized'";
};
