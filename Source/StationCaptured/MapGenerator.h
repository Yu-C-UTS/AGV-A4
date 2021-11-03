// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapPiece.h"
#include "ConnectionPoint.h"
#include "MapGenerator.generated.h"

UCLASS()
class STATIONCAPTURED_API AMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void InitializeMap();

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AMapPiece>> AvaliableMapPieces;

private:
	TArray<UConnectionPoint*> OpenConnectionPoints;
	void spawnNewPiece(TSubclassOf<AMapPiece> mapPieceToSpawn);
};
