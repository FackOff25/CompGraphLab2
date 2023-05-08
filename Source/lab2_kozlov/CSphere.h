// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSphere.generated.h"

UCLASS()
class LAB2_KOZLOV_API ACSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSphere();

		bool SetPosition(float x, float y, float z);
		bool SetPosition(FVector vector);

		void MoveAbsolute(FVector vector);

		void MoveRelative(FVector vector);

		void MoveToPosition();

		void Init(FVector point);

		void AddNewInstance();
		void AddNewInstance(FVector point);

		void SetColor(FLinearColor _color);

		void UpdateColor(FLinearColor _color);

protected:

		UInstancedStaticMeshComponent* Mesh;

		UMaterial* Material;

		float scale = 1.0f;

		FVector position = { 0,0,0 };

		void SetScale(float newScale);

		void UpdateMaterial(FString reference);

		UPROPERTY()
			FLinearColor color = { 0,0,0 };
private:
	UPROPERTY()
		FString MeshReference = "StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'";

		FString MaterialReference = "Material'/Game/StarterContent/Materials/M_Colorized.M_Colorized'";
};
