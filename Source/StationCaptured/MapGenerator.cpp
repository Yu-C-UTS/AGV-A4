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

	for (int i = 0; i < 5; i++)
	{
		//spawnNewPiece(AvaliableMapPieces[FMath::RandRange(0, AvaliableMapPieces.Num() - 1)]);
	}
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::InitializeMap()
{
}

void AMapGenerator::spawnNewPiece(TSubclassOf<AMapPiece> mapPieceToSpawn)
{
	//spawn new piece
	AMapPiece* MapPiece = GetWorld()->SpawnActor<AMapPiece>(mapPieceToSpawn, GetActorLocation(), GetActorRotation());
	MapPiece->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	//find all new connection points
	TArray<UConnectionPoint*> newConnectionPoints;
	TSet<UActorComponent*> components = MapPiece->GetComponents();
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

		MapPiece->AddActorLocalRotation(GetActorRotation() - newConnectionPoints[connectTo]->GetComponentRotation());
		MapPiece->AddActorLocalRotation(GetActorRotation() - OpenConnectionPoints[connectFrom]->GetComponentRotation());
		MapPiece->SetActorLocation(OpenConnectionPoints[connectFrom]->GetComponentLocation());
		MapPiece->AddActorWorldOffset(newConnectionPoints[connectTo]->GetRelativeLocation());
		OpenConnectionPoints.RemoveAt(connectFrom);
		newConnectionPoints.RemoveAt(connectTo);
	}

	//Add new open connection points to list
	for (UActorComponent* component : newConnectionPoints)
	{
		OpenConnectionPoints.Add(Cast<UConnectionPoint>(component));
	}
}


