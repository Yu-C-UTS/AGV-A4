// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"
#include "MapGenerator.h"

AMainGameMode::AMainGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

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

	SpawnHives();
}

void AMainGameMode::Tick(float DeltaTime)
{
	for (int i = ActiveHives.Num() - 1; i >= 0; i--)
	{
		if (!IsValid(ActiveHives[i]))
		{
			ActiveHives.RemoveAt(i);
		}
	}

	if (GEngine)
	{
		if (ActiveHives.Num() <= 0)
		{
			GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Blue, "All Hives Destroyed");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Blue, FString::Printf(TEXT("Active Hive Count: %i"), ActiveHives.Num()));
		}
	}
}

void AMainGameMode::AddHiveSpawnPoint(UHiveSpawnPoint* HiveSpawnPoint)
{
	PossibleHiveSpawnPoints.Add(HiveSpawnPoint);
}

void AMainGameMode::SpawnHives()
{
	if (MapGenerationData->HiveSpawnCount.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Hive Actor assigned for spawning in map generation data"));
		return;
	}

	for (TPair<TSubclassOf<AHive>, int> HiveSpawnCountPair : MapGenerationData->HiveSpawnCount)
	{
		if (HiveSpawnCountPair.Value <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hive spawn count of 0 or lower assigned in map generation data, skipping hive generation."));
			continue;
		}

		for (int i = 0; i < HiveSpawnCountPair.Value; i++)
		{
			if (PossibleHiveSpawnPoints.Num() <= 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("No more hive spawn points avaliable, ending hive generation."));
				return;
			}

			UHiveSpawnPoint* SelectedHiveSpawnPoint = PossibleHiveSpawnPoints[FMath::RandRange(0, PossibleHiveSpawnPoints.Num() - 1)];
			AHive* SpawnedHive = GetWorld()->SpawnActor<AHive>(HiveSpawnCountPair.Key, SelectedHiveSpawnPoint->GetComponentLocation(), SelectedHiveSpawnPoint->GetComponentRotation());
			ActiveHives.Add(SpawnedHive);
			PossibleHiveSpawnPoints.Remove(SelectedHiveSpawnPoint);
		}
	}
}
