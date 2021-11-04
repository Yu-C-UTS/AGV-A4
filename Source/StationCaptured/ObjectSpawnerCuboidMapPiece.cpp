// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSpawnerCuboidMapPiece.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h" 

AObjectSpawnerCuboidMapPiece::AObjectSpawnerCuboidMapPiece()
{
	SpawnVolumeLength = 5000;
	MinSpawnAmount = 5;
	MaxSpawnAmount = 15;
}

void AObjectSpawnerCuboidMapPiece::Initialize()
{
	if (SpawnableObjects.Num() < 1)
	{
		UE_LOG(LogTemp, Error, TEXT("No Spawnable Objects Assigned to Spawner, Aborting Initialization"));
		return;
	}

	int SpawnNum = FMath::RandRange(MinSpawnAmount, MaxSpawnAmount);
	for (int i = 0; i < SpawnNum; i++)
	{
		FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), FVector(SpawnVolumeLength/2));
		AMapObject* SpawnedObject = GetWorld()->SpawnActor<AMapObject>(SpawnableObjects[FMath::RandRange(0, SpawnableObjects.Num() - 1)], SpawnLocation, UKismetMathLibrary::RandomRotator());

	}
}
