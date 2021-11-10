// Fill out your copyright notice in the Description page of Project Settings.


#include "SectorPiece.h"

// Sets default values
ASectorPiece::ASectorPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASectorPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASectorPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASectorPiece::InitializeSectorPiece()
{
	BPInitializeSectorPiece();
}

