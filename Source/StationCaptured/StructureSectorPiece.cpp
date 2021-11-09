// Fill out your copyright notice in the Description page of Project Settings.


#include "StructureSectorPiece.h"
#include "Engine/World.h"

void AStructureSectorPiece::InitializeSectorPiece()
{
	//GenerateStructure();
}

void AStructureSectorPiece::GenerateStructure(int DesiredHeight)
{
	if (!StructureGenerationDataAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("No structure generation data assigned, aborting generation"));
		return;
	}
	if (StructureGenerationDataAsset->AvalibleStructurePieces.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No structure pieces avalible for structure generation, aborting generation"));
		return;
	}

	int GenerateHeight;

	if (DesiredHeight <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Infinite(0) is passed in for structure's AllowedMaxHeight, only generating structure with height of 1 to minimize problems."));
		GenerateHeight = 1;
	}
	else if (StructureGenerationDataAsset->MaxHeight <= 0)
	{
		//Structure possible max gen height is marked 0, assume infinite, using map gen desired height instead.
		GenerateHeight = DesiredHeight;
	}
	else
	{
		GenerateHeight = FMath::Min(DesiredHeight, StructureGenerationDataAsset->MaxHeight);
	}

	for (int i = 0; i < GenerateHeight; i++)
	{
		AStructurePiece* SpawnedPiece = GetWorld()->SpawnActor<AStructurePiece>(StructureGenerationDataAsset->AvalibleStructurePieces[FMath::RandRange(0, StructureGenerationDataAsset->AvalibleStructurePieces.Num() - 1)], FVector(GetActorLocation().X, GetActorLocation().Y, i * 500 + 20 + GetActorLocation().Z), FRotator::ZeroRotator);
		SpawnedPiece->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}
