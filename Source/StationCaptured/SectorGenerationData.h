// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SectorGenerationData.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API USectorGenerationData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		int MinSectorLength;
	UPROPERTY(EditAnywhere)
		int MaxSectorLength;

	UPROPERTY(EditAnywhere)
		int MinSectorHeight;
	UPROPERTY(EditAnywhere)
		int MaxSectorHeight;

	UPROPERTY(EditAnywhere, Category = "Basic Pieces")
		TArray<TSubclassOf<class ASectorPiece>> AvalibleFloorPieces;
	UPROPERTY(EditAnywhere, Category = "Basic Pieces")
		TArray<TSubclassOf<class ASectorPiece>> AvalibleWallPieces;
	UPROPERTY(EditAnywhere, Category = "Basic Pieces")
		TArray<TSubclassOf<class ASectorPiece>> AvalibleRoofPieces;
	UPROPERTY(EditAnywhere, Category = "Basic Pieces")
		TArray<TSubclassOf<class AStructureSectorPiece>> AvalibleStructurePieces;

	UPROPERTY(EditAnywhere, Category = "Connection Pieces")
		TArray<TSubclassOf<class ASectorPiece>> AvalibleFloorConnectionPieces;
	UPROPERTY(EditAnywhere, Category = "Connection Pieces")
		TArray<TSubclassOf<class ASectorPiece>> AvalibleWallConnectionPieces;
	UPROPERTY(EditAnywhere, Category = "Connection Pieces")
		TArray<TSubclassOf<class ASectorPiece>> AvalibleRoofConnectionPieces;
};
