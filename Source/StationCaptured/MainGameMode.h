// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MapGenerationDataAsset.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:
	class AMapGenerator* MapGenerator;

public:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessages) override;

public:
	UPROPERTY(EditAnywhere)
	UMapGenerationDataAsset* MapGenerationData;
};
