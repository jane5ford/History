// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"
#include "PaperSpriteComponent.h"
#include "GraphNode.generated.h"


UCLASS()
class HISTORY_API AGraphNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGraphNode();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Attrubutes")
		int32 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Attrubutes")
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Attrubutes")
		FString Date;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Attrubutes")
		FString Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Attrubutes")
		TSet<int32> EdgeIds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Attrubutes")
		int32 Total;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Attrubutes")
		bool Rotable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Attrubutes")
		bool Seeable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Attrubutes")
		bool Nearby;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* NodeSceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* TextDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* TextDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UPaperSpriteComponent* SpriteComponent;
	
	

	void RotateToPlayer();
	UFUNCTION()
		void PickNode(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);
	UFUNCTION()
		void PickNodes();
	UFUNCTION(BlueprintCallable)
		FVector GenerateLocation();
	UFUNCTION(BlueprintCallable)
		void Locate(int32 nodeId, int32 nodesTotal, bool random);
	UFUNCTION(BlueprintCallable)
		void SetData(FString nodeDescription, FString nodeDate, FString nodeType);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};