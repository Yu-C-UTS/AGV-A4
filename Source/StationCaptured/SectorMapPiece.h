// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapPiece.h"
#include "SectorPiece.h"
#include "SectorGenerationData.h"
#include "SectorMapPiece.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API ASectorMapPiece : public AMapPiece
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	USceneComponent* rootComponent;

public:
	UPROPERTY(EditAnywhere)
	USectorGenerationData* SectorGenerationData;

private:
	void generatePerimeter();
	void generateFloor();
	void populateCells();
};
