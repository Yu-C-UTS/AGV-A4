// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereMapGenerator.h"
#include "Engine/World.h"

ASphereMapGenerator::ASphereMapGenerator()
{
	Radius = 5;
	SectorSize = 5000;
}

void ASphereMapGenerator::BeginPlay()
{
	Super::BeginPlay();

	//InitializeMap();
}

void ASphereMapGenerator::InitializeMap()
{
	//If no map piece is assigned for spawning, log error and return
	if (AvaliableMapPieces.Num() < 1)
	{
		UE_LOG(LogTemp, Error, TEXT("No Map Piece avalible for spawning"));
		return;
	}
	
	//Create Sphere
	for (int x = -Radius; x <= Radius; x++)
	{
		for (int y = -Radius; y <= Radius; y++)
		{
			for (int z = -Radius; z <= Radius; z++)
			{
				//UE_LOG(LogTemp, Warning, TEXT("X:%i Y:%i Z:%i, Radius: %f"), x, y, z, FMath::Sqrt(FMath::Square(x) + FMath::Square(y) + FMath::Square(z)));
				if (FMath::Sqrt(FMath::Square(x) + FMath::Square(y) + FMath::Square(z)) < Radius)
				{
					AMapPiece* SpawnedMapPiece = SpawnNewPiece(AvaliableMapPieces[FMath::RandRange(0, AvaliableMapPieces.Num() - 1)], GetActorLocation() + FVector(x * SectorSize, y * SectorSize, z * SectorSize), GetActorRotation());
					MapPieceMap.Add(FIntVector(x, y, z), SpawnedMapPiece);
					SpawnedMapPiece->Initialize();
				}
			}
		}
	}
}