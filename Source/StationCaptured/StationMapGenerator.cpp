// Fill out your copyright notice in the Description page of Project Settings.


#include "StationMapGenerator.h"

AConnectableMapPiece* AStationMapGenerator::SpawnAndConnectNewMapPiece(TSubclassOf<AConnectableMapPiece> PieceToSpawn, UConnectionPoint* ConnectTo)
{
	AConnectableMapPiece* SpawnedMapPiece = Cast<AConnectableMapPiece>(SpawnNewPiece(PieceToSpawn, GetActorLocation(), GetActorRotation()));

	if (ConnectTo && SpawnedMapPiece)
	{
		UConnectionPoint* ConnectFrom = SpawnedMapPiece->GetConnectionPoints()[FMath::RandRange(0, SpawnedMapPiece->GetConnectionPoints().Num() - 1)];
		SpawnedMapPiece->ConnectAndRepositionMapPiece(ConnectFrom, ConnectTo);
		OpenConnectionPoints.Remove(ConnectTo);
		OpenConnectionPoints.Remove(ConnectFrom);
	}

	//for (UConnectionPoint* ConnectionPoint : SpawnedMapPiece->GetConnectionPoints())
	//{
	//	if (!ConnectionPoint->bIsConnected)
	//	{
	//		OpenConnectionPoints.Add(ConnectionPoint);
	//	}
	//}

	return SpawnedMapPiece;
}

void AStationMapGenerator::InitializeMap()
{
	CreateSectors();
	ConnectSectors();
}

void AStationMapGenerator::CreateSectors()
{	
	/*CreateNewMapPiece(RootComponent, SectorMapPieceToSpawn[0], nullptr);

	for (int i = 1; i < SectorMapPieceToSpawn.Num(); i++)
	{
		if (OpenConnectionPoints.Num() <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Insufficent Connection Points, stopping sector generation."));
			return;
		}
		UConnectionPoint* CorridorConnectionPoints = CreateCorridor(OpenConnectionPoints[FMath::RandRange(0, OpenConnectionPoints.Num() - 1)], FMath::RandRange(1, 3));
		AMapPiece* NewPiece = CreateNewMapPiece(RootComponent, SectorMapPieceToSpawn[i], CorridorConnectionPoints);
	}*/
	for (int i = 0; i < SectorMapPieceToSpawn.Num(); i++)
	{
		SpawnedSectors.Add(Cast<ASectorMapPiece>(SpawnAndConnectNewMapPiece(SectorMapPieceToSpawn[0], nullptr)));
	}
}

void AStationMapGenerator::ConnectSectors()
{
	Algo::SortBy(SpawnedSectors, &ASectorMapPiece::Size, TGreater<>());
	//SpawnedSectors.Sort([](const ASectorMapPiece& LHS, const ASectorMapPiece& RHS) {return LHS.GetSize() > RHS.GetSize(); });
	for (int i = 1; i < SpawnedSectors.Num(); i++)
	{
		if (SpawnedSectors[i]->GetConnectionPoints().Num() <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Terminating Sector connection, no connection point found"));
		}

		int TryCount = 0;
		//Attempt connection to another sector that is already in a correct position
		ASectorMapPiece* ConnectToSector = SpawnedSectors[FMath::RandRange(0, i - 1)];
		while (ConnectToSector->GetOpenConnectionPoints().Num() < 1)
		{
			if (TryCount > 10)
			{
				//Attempted to connect to an open connection for too long, failing attempt and throwing an error
				//UE_LOG(LogTemp, Fatal, TEXT("Sector connection failed, no open connection found, terminating."));
				return;
			}

			//If the chosen sector doesn't have an open connection point
			ConnectToSector = SpawnedSectors[FMath::RandRange(0, i - 1)];
			TryCount++;
		}
		UConnectionPoint* ConnectToPoint = CreateCorridor(ConnectToSector->GetOpenConnectionPoints()[FMath::RandRange(0, ConnectToSector->GetOpenConnectionPoints().Num() - 1)], FMath::RandRange(1, 3));
		SpawnedSectors[i]->ConnectAndRepositionMapPiece(SpawnedSectors[i]->GetOpenConnectionPoints()[0], ConnectToPoint);
	}
}

UConnectionPoint* AStationMapGenerator::CreateCorridor(UConnectionPoint* OriginConnectionPoint, int CorridorLength)
{
	if (OriginConnectionPoint->bIsConnected)
	{
		UE_LOG(LogTemp, Warning, TEXT("ConnectionPoint: %s is marked connected."), OriginConnectionPoint);
	}

	AConnectableMapPiece* NewCorridorMapPiece = SpawnAndConnectNewMapPiece(AvaliableCorridorMapPieces[FMath::RandRange(0, AvaliableCorridorMapPieces.Num() - 1)], OriginConnectionPoint);

	//Check every connection point on the new corridor piece, get an open connection from it, and either return it if the corridor is done, or spawn another new corridor piece if needed.
	for (UConnectionPoint* ConnectionPoint : NewCorridorMapPiece->GetConnectionPoints())
	{
		if (!ConnectionPoint->bIsConnected)
		{
			if (CorridorLength == 0)
			{
				OpenConnectionPoints.Add(ConnectionPoint);
				return ConnectionPoint;
			}
			return CreateCorridor(ConnectionPoint, CorridorLength - 1);
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Hit Deadend when creating corridor"));
	return nullptr;
}

AMapPiece* AStationMapGenerator::SpawnNewPiece(TSubclassOf<AMapPiece> MapPieceToSpawn, FVector SpawnLocation, FRotator SpawnRotation)
{
	AMapPiece* SpawnedMapPiece = AMapGenerator::SpawnNewPiece(MapPieceToSpawn, SpawnLocation, SpawnRotation);

	//find all new connection points
	TArray<UConnectionPoint*> newConnectionPoints;
	TSet<UActorComponent*> components = SpawnedMapPiece->GetComponents();
	for (UActorComponent* component : components)
	{
		if (component && component->IsA<UConnectionPoint>())
		{
			newConnectionPoints.Add(Cast<UConnectionPoint>(component));
		}
	}
	
	//connect new piece
	if (OpenConnectionPoints.Num() != 0)
	{
		int connectFrom = FMath::RandRange(0, OpenConnectionPoints.Num() - 1);
		int connectTo = FMath::RandRange(0, newConnectionPoints.Num() - 1);
	
		SpawnedMapPiece->AddActorLocalRotation(GetActorRotation() - newConnectionPoints[connectTo]->GetComponentRotation());
		SpawnedMapPiece->AddActorLocalRotation(GetActorRotation() - OpenConnectionPoints[connectFrom]->GetComponentRotation());
		SpawnedMapPiece->SetActorLocation(OpenConnectionPoints[connectFrom]->GetComponentLocation());
		SpawnedMapPiece->AddActorWorldOffset(newConnectionPoints[connectTo]->GetRelativeLocation());
		OpenConnectionPoints.RemoveAt(connectFrom);
		newConnectionPoints.RemoveAt(connectTo);
	}
	
	//Add new open connection points to list
	for (UActorComponent* component : newConnectionPoints)
	{
		OpenConnectionPoints.Add(Cast<UConnectionPoint>(component));
	}
	
	return SpawnedMapPiece;
}