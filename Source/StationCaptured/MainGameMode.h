// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Hive.h"
#include "HiveSpawnPoint.h"
#include "MapGenerationDataAsset.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMainGameMode();

private:
	class AMapGenerator* MapGenerator;

public:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessages) override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	UMapGenerationDataAsset* MapGenerationData;

public:
	UFUNCTION(BlueprintCallable)
	void AddHiveSpawnPoint(UHiveSpawnPoint* HiveSpawnPoint);

private:
	void SpawnHives();
	TArray<UHiveSpawnPoint*> PossibleHiveSpawnPoints;
	TArray<AHive*> ActiveHives;
};
