// Fill out your copyright notice in the Description page of Project Settings.

#include "Lab2Scene.h"
#include "Graph.h"
#include "GraphWalker.h"
#include "ConfigReader.h"
#include "Misc/Paths.h"
#include "GameFramework/PlayerStart.h"

// Sets default values
ALab2Scene::ALab2Scene()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));
	SetActorLocation(FVector(0, 0, 0));
}

// Called when the game starts or when spawned
void ALab2Scene::BeginPlay()
{
	TMap<FString, FString> cfg = UConfigReader::ReadConfig(FPaths::ProjectDir() + FString("\\Config\\Lab2.ini"));
	//if (cfg.Num() == 0) return;

	UWorld* world = GetWorld();

	AGraph* graph = world->SpawnActor<AGraph>();
	
	FString* sizeXstr = cfg.Find(L"SizeX");
	FString* sizeYstr = cfg.Find(L"SizeY");
	FString* dispercestr = cfg.Find(L"Disperce");
	FString* walkerCountstr = cfg.Find(L"Walkers");

	int sizeX = sizeXstr == NULL ? FMath::RandRange(3, 6) : FCString::Atoi((TCHAR*)**sizeXstr);
	int sizeY = sizeYstr == NULL ? FMath::RandRange(3, 8) : FCString::Atoi((TCHAR*)**sizeYstr);
	int disperce = dispercestr == NULL ? 35 : FCString::Atoi((TCHAR*)**dispercestr);
	int walkerCount = walkerCountstr == NULL ? FMath::RandRange(1, 3) : FCString::Atoi((TCHAR*)**walkerCountstr);


	graph->Init(sizeX, sizeY, disperce);

	for (int i = 0; i < walkerCount; ++i) {
		int start = FMath::RandRange(0, sizeX * sizeY - 1);
		int end = start + FMath::RandRange(1, sizeX * sizeY - 3);
		end = end % (sizeX * sizeY);
		AGraphWalker* walker = world->SpawnActor<AGraphWalker>();
		walker->SetParams(graph->GetSizeX(), graph->GetSizeY(), graph->GetVertexes(), graph->GetEdges(), start, end, 1);
	}
}


