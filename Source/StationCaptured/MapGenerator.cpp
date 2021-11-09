// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"
#include "Engine/World.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::InitializeMap()
{
}

AMapPiece* AMapGenerator::SpawnNewPiece(TSubclassOf<AMapPiece> MapPieceToSpawn, FVector SpawnLocation, FRotator SpawnRotation)
{
	//spawn new piece
	AMapPiece* MapPiece = GetWorld()->SpawnActor<AMapPiece>(MapPieceToSpawn, SpawnLocation, SpawnRotation);
	MapPiece->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	MapPiece->Initialize();

	return MapPiece;
}


