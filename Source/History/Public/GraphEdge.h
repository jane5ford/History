// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "GraphNode.h"
#include "GraphEdge.generated.h"

UCLASS()
class HISTORY_API AGraphEdge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGraphEdge();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge Attributes")
		int32 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge Attributes")
		AGraphNode* NodeA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge Attributes")
		AGraphNode* NodeB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge Attributes")
		bool Rotable = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* NodeSceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* PS;
	void Create(AGraphNode* nodeA, AGraphNode* nodeB);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
