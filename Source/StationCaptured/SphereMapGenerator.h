// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerator.h"
#include "SphereMapGenerator.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API ASphereMapGenerator : public AMapGenerator
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:
	ASphereMapGenerator();

public:
	UPROPERTY(EditDefaultsOnly)
	int Radius;
	UPROPERTY(EditDefaultsOnly)
	float SectorSize;
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AMapPiece>> AvaliableMapPieces;

public:
	virtual void InitializeMap() override;

private:
	TMap<FIntVector,AMapPiece*> MapPieceMap;
};
