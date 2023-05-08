// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicEdge.h"

ADynamicEdge::ADynamicEdge() {
	height = 0.02;
	level = 0.01;
}

void ADynamicEdge::UpdateStart(FVector newStart, int instanceId) {
	instanceInfo[instanceId].start = newStart;
	UpdateEdge(instanceId);
}

void ADynamicEdge::UpdateEnd(FVector newEnd, int instanceId) {
	instanceInfo[instanceId].end = newEnd;
	UpdateEdge(instanceId);
}

void ADynamicEdge::UpdateEdge(int instanceId) {
	FVector edgeVector = instanceInfo[instanceId].end - instanceInfo[instanceId].start;
	FRotator rotation = edgeVector.Rotation();
	rotation.Pitch = 90;
	rotation.Roll += 180;
	FVector transform(instanceInfo[instanceId].height, instanceInfo[instanceId].height, edgeVector.Size() / 100);
	Mesh->UpdateInstanceTransform(instanceId, FTransform(rotation, instanceInfo[instanceId].start, transform));
	Mesh->MarkRenderStateDirty();
}
