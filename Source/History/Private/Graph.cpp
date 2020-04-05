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




void AGraph::ReadFromTxtFile()
{
	//TArray<FString> nodesArray;
	//if (FFileHelper::LoadFileToStringArray(nodesArray, *(FPaths::ConvertRelativePathToFull(FPaths::GameContentDir()) + "/Test/Data/e14.in"))) {
	//	int32 k = 0;
	//	FString res;
	//	FString res1, res2;
	//	AGraphNode* node;
	//	FString IntAsString = FString::FromInt(nodesArray.Num());


	//	int32 total = nodesArray.Num() / 2;
	//	for (int32 i = 1; i <= total; i++)
	//	{
	//		nodesArray[k].Split(":", &res1, &res2);
	//		node = (AGraphNode*)SpawnNodeBP(res1);

	//		if (node) {

	//			node->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	//			node->SetData(res2, nodesArray[k + 1], res1);
	//			node->Locate(i, total, IsRandom);
	//			Nodes.Add(i, node);
	//			k = k + 2;
	//		}
	//	}
	//	if (Nodes.Num() > 0) {
	//		TArray<FString> adjacencyArray;
	//		if (FFileHelper::LoadFileToStringArray(adjacencyArray, *(FPaths::ConvertRelativePathToFull(FPaths::GameContentDir()) + "/Test/e14.in"))) {

	//			//UKismetSystemLibrary::PrintString(this, "Nodes and Edges: " + result[0], true, true, FLinearColor(0, 0, 0, 1), 100.f);
	//			AGraphEdge* edge;
	//			for (int32 i = 1; i < adjacencyArray.Num(); i++) {
	//				res = adjacencyArray[i];
	//				res.Split(" ", &res1, &res2);
	//				int32 nodeA_id = FCString::Atoi(*res1);
	//				int32 nodeB_id = FCString::Atoi(*res2);
	//				edge = SpawnEdge(i, nodeA_id, nodeB_id);
	//				Edges.Add(i, edge);
	//				Nodes[nodeA_id]->EdgeIds.Add(i);
	//				Nodes[nodeB_id]->EdgeIds.Add(i);
	//			}
	//		}
	//		else UE_LOG(LogTemp, Warning, TEXT("File 1 Not Found"));
	//	}
	//}
	//else UE_LOG(LogTemp, Warning, TEXT("File 2 Not Found"));
}

AGraphNode* AGraph::SpawnNodeBP(int32 id, FString type, FString text, FString date)
{
	//UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/BP_GraphNode.BP_GraphNode'")));

	UBlueprint* GeneratedBP = Cast<UBlueprint>(GraphNode);
	/*if (!SpawnActor) {
		UE_LOG(LogTemp, Warning, TEXT("CANT FIND OBJECT TO SPAWN"));
		return NULL;
	}*/

	UClass* SpawnClass = GraphNode->StaticClass();
	if (SpawnClass == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("CLASS == NULL"));
		UKismetSystemLibrary::PrintString(this, "Class is not found", true, true, FLinearColor(1, 1, 1, 1), 1000.f);
		return NULL;
	}

	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AGraphNode* node = (AGraphNode*)World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	if (node) {
		UKismetSystemLibrary::PrintString(this, "Node is spawned", true, true, FLinearColor(1, 1, 1, 1), 1000.f);
		node->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		node->SetData(text, date, type);
		node->Locate(id, NodesCount, IsRandom);
	}
	return node;
}

AGraphEdge* AGraph::SpawnEdge(int32 id, int32 nodeA_id, int32 nodeB_id)
{
	AGraphNode* nodeA;
	AGraphNode* nodeB;
	nodeA = (AGraphNode*)Nodes[nodeA_id];
	nodeB = (AGraphNode*)Nodes[nodeB_id];
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

