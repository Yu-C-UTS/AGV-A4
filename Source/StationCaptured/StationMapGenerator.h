// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerator.h"
#include "SectorMapPiece.h"
#include "StationMapGenerator.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API AStationMapGenerator : public AMapGenerator
{
	GENERATED_BODY()
	
public:
	virtual void InitializeMap() override;

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AConnectableMapPiece>> AvaliableCorridorMapPieces;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ASectorMapPiece>> SectorMapPieceToSpawn;

private:
	TArray<ASectorMapPiece*> SpawnedSectors;

private:
	AConnectableMapPiece* SpawnAndConnectNewMapPiece(TSubclassOf<AConnectableMapPiece> PieceToSpawn, UConnectionPoint* ConnectTo);
	void CreateSectors();
	void ConnectSectors();
	UConnectionPoint* CreateCorridor(UConnectionPoint* OriginConnectionPoint, int CorridorLength);

protected:
	virtual AMapPiece* SpawnNewPiece(TSubclassOf<AMapPiece> MapPieceToSpawn, FVector SpawnLocation, FRotator SpawnRotation) override;
};
