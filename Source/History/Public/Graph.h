// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "Graph.generated.h"


UCLASS()
class HISTORY_API AGraph : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGraph();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* NodeSceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 NodesCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EdgesCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph Content")
		TMap<int32, AGraphNode*> Nodes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graph Content")
		TMap<int32, AGraphEdge*> Edges;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsRandom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UObject* GraphNode;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AGraphNode> ToSpawn;
	UFUNCTION(BlueprintCallable) AGraphNode* SpawnNodeBP(int32 id, FString type, FString text, FString date);
	UFUNCTION(BlueprintCallable) AGraphEdge* SpawnEdge(int32 id, int32 nodeA_id, int32 nodeB_id);

	UFUNCTION(BlueprintCallable) void GenerateLocationForNodes();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
