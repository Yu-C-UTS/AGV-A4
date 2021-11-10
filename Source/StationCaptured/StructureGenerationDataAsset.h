// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StructurePiece.h"
#include "StructureGenerationDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API UStructureGenerationDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	int MaxHeight; //Fill in 0 if max structure height is not enforced for this structure

	UPROPERTY(EditAnywhere)
	bool AllowRotation;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AStructurePiece>> AvalibleStructurePieces;
};
