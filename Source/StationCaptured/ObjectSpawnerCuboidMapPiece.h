// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapPiece.h"
#include "MapObject.h"
#include "ObjectSpawnerCuboidMapPiece.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API AObjectSpawnerCuboidMapPiece : public AMapPiece
{
	GENERATED_BODY()

public:
	AObjectSpawnerCuboidMapPiece();

public:
	UPROPERTY(EditAnywhere)
	int MinSpawnAmount;
	UPROPERTY(EditAnywhere)
	int MaxSpawnAmount;
	UPROPERTY(EditAnywhere)
	float SpawnVolumeLength;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AMapObject>> SpawnableObjects;

public:
	virtual void Initialize() override;
};
