// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MapGenerationDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API UMapGenerationDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AMapGenerator> MainMapGenerator;
	//UPROPERTY(EditDefaultsOnly)
	//TArray<TSubclassOf<class AMapPiece>> AvalibleGeneralMapPieces;
};
