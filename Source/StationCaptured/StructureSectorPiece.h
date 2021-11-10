// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SectorPiece.h"
#include "StructureGenerationDataAsset.h"
#include "StructureSectorPiece.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API AStructureSectorPiece : public ASectorPiece
{
	GENERATED_BODY()
	
public:
	virtual void InitializeSectorPiece() override;

public:
	UPROPERTY(EditAnywhere)
	UStructureGenerationDataAsset* StructureGenerationDataAsset;

public:
	UPROPERTY(EditAnywhere, Category = "Test")
	int TestHeight;
	//UFUNCTION(CallInEditor, Category = "Test")
	//void GenerateStructureTest();
	void GenerateStructure(int DesiredHeight);

};
