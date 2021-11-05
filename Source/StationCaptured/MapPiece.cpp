// Fill out your copyright notice in the Description page of Project Settings.


#include "MapPiece.h"

// Sets default values
AMapPiece::AMapPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);
}

// Called when the game starts or when spawned
void AMapPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapPiece::Initialize()
{
	BPInitialize();
}

