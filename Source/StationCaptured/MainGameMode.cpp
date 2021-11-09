// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Engine/World.h"
#include "MapGenerator.h"

void AMainGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessages)
{
	Super::InitGame(MapName, Options, ErrorMessages);

	if (!MapGenerationData)
	{
		UE_LOG(LogTemp, Error, TEXT("No MapGenerationData Assigned in GameMode"));
		return;
	}

	if (!MapGenerationData->MainMapGenerator)
	{
		UE_LOG(LogTemp, Error, TEXT("No Map Generation Assigned in Map Generation Data"));
		return;
	}
	MapGenerator = GetWorld()->SpawnActor<AMapGenerator>(MapGenerationData->MainMapGenerator);

	//if (MapGenerationData->AvalibleGeneralMapPieces.Num() < 1)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("No General Map Piece Assigned in Map Generation Data, ignore if this is intended."));
	//}
	//MapGenerator->AvaliableMapPieces = MapGenerationData->AvalibleGeneralMapPieces;

	MapGenerator->InitializeMap();
}
