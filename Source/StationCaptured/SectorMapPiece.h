// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConnectableMapPiece.h"
#include "SectorPiece.h"
#include "StructureSectorPiece.h"
#include "SectorGenerationData.h"
#include "SectorMapPiece.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API ASectorMapPiece : public AConnectableMapPiece
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	USectorGenerationData* SectorGenerationData;

private:
	int SectorHeight;
	int SectorLength;
	int SectorWidth;

	TArray<FVector2DHalf> ConnectionPointPositions;

protected:
	virtual void Initialize() override;
	ASectorPiece* CreateNewSectorPiece(TSubclassOf<ASectorPiece> PieceToSpawn, FVector SpawnLocation, FRotator SpawnRotation);

private:
	void InitilizeSectorParameters();
	void GeneratePerimeter();
	void GenerateFloor();
	void PopulateCells();
	void Roofing();
};
