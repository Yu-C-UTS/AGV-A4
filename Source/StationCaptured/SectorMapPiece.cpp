// Fill out your copyright notice in the Description page of Project Settings.


#include "SectorMapPiece.h"
#include "Engine/World.h"

void ASectorMapPiece::Initialize()
{
	AConnectableMapPiece::Initialize();

	if (!SectorGenerationData)
	{
		UE_LOG(LogTemp, Error, TEXT("SectorData not assigned"));
		return;
	}

	InitilizeSectorParameters();
	GeneratePerimeter();
	GenerateFloor();
	PopulateCells();
	Roofing();
}

ASectorPiece* ASectorMapPiece::CreateNewSectorPiece(TSubclassOf<ASectorPiece> PieceToSpawn, FVector SpawnLocation, FRotator SpawnRotation)
{
	if (!PieceToSpawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Null piece assigned for spawning, terminating spawn"));
		return nullptr;
	}

	ASectorPiece* SpawnedPiece = GetWorld()->SpawnActor<ASectorPiece>(PieceToSpawn, SpawnLocation, SpawnRotation);
	SpawnedPiece->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	//Find and register all ConnectionPoint components in the new sub-piece
	TSet<UActorComponent*> ActorComponents = SpawnedPiece->GetComponents();
	for (UActorComponent* Component : ActorComponents)
	{
		if (Component && Component->IsA<UConnectionPoint>())
		{
			ConnectionPoints.Add(Cast<UConnectionPoint>(Component));
		}
	}

	return SpawnedPiece;
}

void ASectorMapPiece::InitilizeSectorParameters()
{
	SectorLength = FMath::RandRange(SectorGenerationData->MinSectorLength, SectorGenerationData->MaxSectorLength);
	SectorWidth = FMath::RandRange(SectorGenerationData->MinSectorLength, SectorGenerationData->MaxSectorLength);
	SectorHeight = FMath::RandRange(SectorGenerationData->MinSectorHeight, SectorGenerationData->MaxSectorHeight);

	Size = SectorHeight * SectorLength * SectorHeight;

	ConnectionPointPositions.SetNum(6);
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0: //Floor
		case 1: //Roof
			ConnectionPointPositions[i] = FVector2DHalf(FMath::RandRange(0, SectorWidth - 1), FMath::RandRange(0, SectorLength - 1));
			break;

		case 2: //Widthwise walls
		case 3:
			ConnectionPointPositions[i] = FVector2DHalf(FMath::RandRange(0, SectorWidth - 1), FMath::RandRange(0, SectorHeight - 1));
			break;

		case 4: //Lengthwise walls
		case 5:
			ConnectionPointPositions[i] = FVector2DHalf(FMath::RandRange(0, SectorLength - 1), FMath::RandRange(0, SectorHeight - 1));
			break;

		default:
			UE_LOG(LogTemp, Error, TEXT("Invalid sector connection point position initilization attempt."));
			break;
		}
	}
}

void ASectorMapPiece::GeneratePerimeter()
{
	if (SectorGenerationData->AvalibleWallPieces.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No AvalibleWallPiece assigned in sector generation data"));
		return;
	}
	
	if (SectorGenerationData->AvalibleWallConnectionPieces.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No AvalibleWallConnectionPiece assigned in sector generation data"));
		return;
	}

	//ASectorPiece* newSectorPiece;

	for (int z = 0; z < SectorHeight; z++)
	{
		for (int y = 0; y < SectorLength; y++)
		{
			if (ConnectionPointPositions[4].X == y && ConnectionPointPositions[4].Y == z && SectorGenerationData->AvalibleWallConnectionPieces.Num() > 0)
			{
				//UE_LOG(LogTemp, Display, TEXT("Z: %i, Y: %i , X: %f, Y: %f"), z, y, ConnectionPointPositions[4].X.GetFloat(), ConnectionPointPositions[4].Y.GetFloat());

				//Spawn a connection piece
				CreateNewSectorPiece(SectorGenerationData->AvalibleWallConnectionPieces[FMath::RandRange(0, SectorGenerationData->AvalibleWallConnectionPieces.Num() - 1)], FVector(y * 1500 + 750, 0, z * 500), FRotator::ZeroRotator);
			}
			else
			{
				//Spawn a normal wall piece
				CreateNewSectorPiece(SectorGenerationData->AvalibleWallPieces[FMath::RandRange(0, SectorGenerationData->AvalibleWallPieces.Num() - 1)], FVector(y * 1500 + 750, 0, z * 500), FRotator::ZeroRotator);
			}

			if (ConnectionPointPositions[5].X == y && ConnectionPointPositions[5].Y == z && SectorGenerationData->AvalibleWallConnectionPieces.Num() > 0)
			{
				//Spawn a connection piece
				CreateNewSectorPiece(SectorGenerationData->AvalibleWallConnectionPieces[FMath::RandRange(0, SectorGenerationData->AvalibleWallConnectionPieces.Num() - 1)], FVector(y * 1500 + 750, SectorWidth * 1500, z * 500), FRotator(0, 180, 0));
			}
			else
			{
				//Spawn a normal wall piece
				CreateNewSectorPiece(SectorGenerationData->AvalibleWallPieces[FMath::RandRange(0, SectorGenerationData->AvalibleWallPieces.Num() - 1)], FVector(y * 1500 + 750, SectorWidth * 1500, z * 500), FRotator(0, 180, 0));
			}
		}

		//Widthwise walls
		for (int x = 0; x < SectorWidth; x++)
		{
			if (ConnectionPointPositions[2].X == x && ConnectionPointPositions[2].Y == z && SectorGenerationData->AvalibleWallConnectionPieces.Num() > 0)
			{
				//Spawn a connection piece
				CreateNewSectorPiece(SectorGenerationData->AvalibleWallConnectionPieces[FMath::RandRange(0, SectorGenerationData->AvalibleWallConnectionPieces.Num() - 1)], FVector(0, x * 1500 + 750, z * 500), FRotator(0, 270, 0));
			}
			else
			{
				CreateNewSectorPiece(SectorGenerationData->AvalibleWallPieces[FMath::RandRange(0, SectorGenerationData->AvalibleWallPieces.Num() - 1)], FVector(0, x * 1500 + 750, z * 500), FRotator(0, 270, 0));
			}

			if (ConnectionPointPositions[3].X == x && ConnectionPointPositions[3].Y == z && SectorGenerationData->AvalibleWallConnectionPieces.Num() > 0)
			{
				//Spawn a connection piece
				CreateNewSectorPiece(SectorGenerationData->AvalibleWallConnectionPieces[FMath::RandRange(0, SectorGenerationData->AvalibleWallConnectionPieces.Num() - 1)], FVector(SectorLength * 1500, x * 1500 + 750, z * 500), FRotator(0, 90, 0));
			}
			else
			{
				CreateNewSectorPiece(SectorGenerationData->AvalibleWallPieces[FMath::RandRange(0, SectorGenerationData->AvalibleWallPieces.Num() - 1)], FVector(SectorLength * 1500, x * 1500 + 750, z * 500), FRotator(0, 90, 0));
			}
		}
	}
}

void ASectorMapPiece::GenerateFloor()
{
	if (SectorGenerationData->AvalibleFloorPieces.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No AvalibleFloorPiece assigned in sector generation data"));
		return;
	}

	for (int x = 0; x < SectorWidth; x++)
	{
		for (int y = 0; y < SectorLength; y++)
		{
			if (ConnectionPointPositions[0].X == x && ConnectionPointPositions[0].Y == y && SectorGenerationData->AvalibleFloorConnectionPieces.Num() > 0)
			{
				//Spawn a connection piece
				CreateNewSectorPiece(SectorGenerationData->AvalibleFloorConnectionPieces[FMath::RandRange(0, SectorGenerationData->AvalibleFloorConnectionPieces.Num() - 1)], FVector(y * 1500 + 750, x * 1500 + 750, 0), FRotator::ZeroRotator);
			}
			else
			{
				CreateNewSectorPiece(SectorGenerationData->AvalibleFloorPieces[FMath::RandRange(0, SectorGenerationData->AvalibleFloorPieces.Num() - 1)], FVector(y * 1500 + 750, x * 1500 + 750, 0), FRotator::ZeroRotator);
			}
		}
	}
}

void ASectorMapPiece::PopulateCells()
{
	if (SectorGenerationData->AvalibleStructurePieces.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No AvalibleBuildingPiece assigned in sector generation data"));
		return;
	}

	for (int x = 0; x < SectorWidth; x++)
	{
		for (int y = 0; y < SectorLength; y++)
		{
			int GenerateStructureIndex = FMath::RandRange(0, SectorGenerationData->AvalibleStructurePieces.Num());
			//Using Max Index + 1 as "Not generate Structure"
			if (GenerateStructureIndex == SectorGenerationData->AvalibleStructurePieces.Num())
			{
				continue;
			}
			AStructureSectorPiece* SpawnedStructure = GetWorld()->SpawnActor<AStructureSectorPiece>(SectorGenerationData->AvalibleStructurePieces[GenerateStructureIndex], FVector(y * 1500 + 750, x * 1500 + 750, 0), FRotator::ZeroRotator);
			SpawnedStructure->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			SpawnedStructure->GenerateStructure(FMath::RandRange(1, SectorHeight));
		}
	}
}

void ASectorMapPiece::Roofing()
{
	if (SectorGenerationData->AvalibleRoofPieces.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No AvalibleRoofPiece assigned in sector generation data"));
		return;
	}

	for (int x = 0; x < SectorWidth; x++)
	{
		for (int y = 0; y < SectorLength; y++)
		{
			if (ConnectionPointPositions[0].X == x && ConnectionPointPositions[0].Y == y && SectorGenerationData->AvalibleRoofConnectionPieces.Num() > 0)
			{
				//Spawn a connection piece
				CreateNewSectorPiece(SectorGenerationData->AvalibleRoofConnectionPieces[FMath::RandRange(0, SectorGenerationData->AvalibleRoofConnectionPieces.Num() - 1)], FVector(y * 1500 + 750, x * 1500 + 750, SectorHeight * 500 + 20), FRotator::ZeroRotator);
			}
			else
			{
				CreateNewSectorPiece(SectorGenerationData->AvalibleRoofPieces[FMath::RandRange(0, SectorGenerationData->AvalibleRoofPieces.Num() - 1)], FVector(y * 1500 + 750, x * 1500 + 750, SectorHeight * 500 + 20), FRotator::ZeroRotator);
			}
		}
	}
}
