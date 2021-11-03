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
	int SectorLength;
	UPROPERTY(EditAnywhere)
	int SectorWidth;
	UPROPERTY(EditAnywhere)
	int SectorHeight;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ASectorPiece>> AvalibleFloorPieces;	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ASectorPiece>> AvalibleWallPieces;	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ASectorPiece>> AvalibleBuildingPieces;
};
