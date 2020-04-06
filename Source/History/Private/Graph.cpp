// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Misc/FileHelper.h"
#include <Runtime\Core\Public\Misc\Paths.h>
#include "UObject/ConstructorHelpers.h"
#include <Runtime\Engine\Classes\Kismet\KismetSystemLibrary.h>

// Sets default values
AGraph::AGraph()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NodeSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NodeScene"));
	NodeSceneComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	RootComponent = NodeSceneComponent;
}

// Called when the game starts or when spawned
void AGraph::BeginPlay()
{
	Super::BeginPlay();
	
}

AGraphNode* AGraph::SpawnNodeBP(int32 id, FString type, FString text, FString date)
{
	AGraphNode* node = NULL;

	if (ToSpawn) {
		UWorld* World = GetWorld();
		if (World) {
			FActorSpawnParameters spawnParams;
			node = World->SpawnActor<AGraphNode>(ToSpawn, GetActorLocation(), GetActorRotation(), spawnParams);
		}
	}
	if (node) {
		node->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		node->SetData(text, date, type);
		node->Locate(id, NodesCount, IsRandom);
		return node;
	}
	else {
		UKismetSystemLibrary::PrintString(this, "NODE IS NOT SPAWNED", true, true, FLinearColor(1, 1, 1, 1), 1000.f);
		return NULL;
	}
}

AGraphEdge* AGraph::SpawnEdge(int32 id, int32 nodeA_id, int32 nodeB_id)
{
	AGraphNode* nodeA;
	AGraphNode* nodeB;
	nodeA = (AGraphNode*)Nodes[nodeA_id];
	nodeB = (AGraphNode*)Nodes[nodeB_id];
	nodeA->EdgeIds.Add(id);
	nodeB->EdgeIds.Add(id);
	AGraphEdge* edge = GetWorld()->SpawnActor<AGraphEdge>();
	edge->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	edge->Create(nodeA, nodeB);
	edge->Id = id;
	return edge;
}

void AGraph::GenerateLocationForNodes()
{
	for (int32 i = 1; i <= Nodes.Num(); i++) {
		FVector location = Nodes[i]->GenerateLocation();
	}
}

// Called every frame
void AGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

