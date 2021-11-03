// Fill out your copyright notice in the Description page of Project Settings.


#include "SectorMapPiece.h"
#include "Engine/World.h"

void ASectorMapPiece::BeginPlay()
{
	Super::BeginPlay();

	if (!SectorGenerationData)
	{
		UE_LOG(LogTemp, Error, TEXT("SectorData not assigned"));
		return;
	}

	rootComponent = FindComponentByClass<USceneComponent>();
	
	if (!rootComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("no scene component found for root"));
		return;
	}

	generatePerimeter();
	generateFloor();
	populateCells();
}

void ASectorMapPiece::generatePerimeter()
{
	if (SectorGenerationData->AvalibleWallPieces.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No AvalibleWallPiece assigned in sector generation data"));
		return;
	}
	
	ASectorPiece* newSectorPiece;

	for (int z = 0; z < SectorGenerationData->SectorHeight; z++)
	{
		for (int y = 0; y < SectorGenerationData->SectorLength; y++)
		{
			newSectorPiece = GetWorld()->SpawnActor<ASectorPiece>(SectorGenerationData->AvalibleWallPieces[FMath::RandRange(0, SectorGenerationData->AvalibleWallPieces.Num() - 1)], FVector(y * 1500 + 750, 0, z * 500), FRotator::ZeroRotator);
			newSectorPiece->AttachToComponent(rootComponent, FAttachmentTransformRules::KeepWorldTransform);

			newSectorPiece = GetWorld()->SpawnActor<ASectorPiece>(SectorGenerationData->AvalibleWallPieces[FMath::RandRange(0, SectorGenerationData->AvalibleWallPieces.Num() - 1)], FVector(y * 1500 + 750, SectorGenerationData->SectorWidth * 1500, z * 500), FRotator(0, 180, 0));
			newSectorPiece->AttachToComponent(rootComponent, FAttachmentTransformRules::KeepWorldTransform);
		}
		for (int x = 0; x < SectorGenerationData->SectorWidth; x++)
		{
			newSectorPiece = GetWorld()->SpawnActor<ASectorPiece>(SectorGenerationData->AvalibleWallPieces[FMath::RandRange(0, SectorGenerationData->AvalibleWallPieces.Num() - 1)], FVector(0, x * 1500 + 750, z * 500), FRotator(0, 270, 0));
			newSectorPiece->AttachToComponent(rootComponent, FAttachmentTransformRules::KeepWorldTransform);

			newSectorPiece = GetWorld()->SpawnActor<ASectorPiece>(SectorGenerationData->AvalibleWallPieces[FMath::RandRange(0, SectorGenerationData->AvalibleWallPieces.Num() - 1)], FVector(SectorGenerationData->SectorLength * 1500, x * 1500 + 750, z * 500), FRotator(0, 90, 0));
			newSectorPiece->AttachToComponent(rootComponent, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

void ASectorMapPiece::generateFloor()
{
	if (SectorGenerationData->AvalibleFloorPieces.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No AvalibleFloorPiece assigned in sector generation data"));
		return;
	}
	
	ASectorPiece* newSectorPiece;

	for (int x = 0; x < SectorGenerationData->SectorWidth; x++)
	{
		for (int y = 0; y < SectorGenerationData->SectorLength; y++)
		{
			newSectorPiece = GetWorld()->SpawnActor<ASectorPiece>(SectorGenerationData->AvalibleFloorPieces[FMath::RandRange(0, SectorGenerationData->AvalibleFloorPieces.Num() - 1)], FVector(y * 1500 + 750, x * 1500 + 750, 0), FRotator::ZeroRotator);
			newSectorPiece->AttachToComponent(rootComponent, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

void ASectorMapPiece::populateCells()
{
	if (SectorGenerationData->AvalibleBuildingPieces.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No AvalibleBuildingPiece assigned in sector generation data"));
		return;
	}

	ASectorPiece* newSectorPiece;

	for (int x = 0; x < SectorGenerationData->SectorWidth; x++)
	{
		for (int y = 0; y < SectorGenerationData->SectorLength; y++)
		{
			int cellHeight = FMath::RandRange(0, SectorGenerationData->SectorHeight);
			for (int z = 0; z < cellHeight; z++)
			{
				newSectorPiece = GetWorld()->SpawnActor<ASectorPiece>(SectorGenerationData->AvalibleBuildingPieces[FMath::RandRange(0, SectorGenerationData->AvalibleBuildingPieces.Num() - 1)], FVector(y * 1500 + 750, x * 1500 + 750, z * 500 + 20), FRotator::ZeroRotator);
				newSectorPiece->AttachToComponent(rootComponent, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}
}
