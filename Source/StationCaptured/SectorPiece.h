// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SectorPiece.generated.h"

UCLASS()
class STATIONCAPTURED_API ASectorPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASectorPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void InitializeSectorPiece();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void BPInitializeSectorPiece();
};
