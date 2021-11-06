// Fill out your copyright notice in the Description page of Project Settings.


#include "Hive.h"
#include "Engine/World.h"

// Sets default values
AHive::AHive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnInterval = 5.0f;
}

// Called when the game starts or when spawned
void AHive::BeginPlay()
{
	Super::BeginPlay();
	ActiveSpawn = 0;
}

// Called every frame
void AHive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHive::SpawnEnemy(float DeltaTime)
{
	AEnemyFlyingAI* SpawnedEnemy;
	//Countdown for spawn
	if(SpawnInterval > 0)
	{
		SpawnInterval -= DeltaTime;
		return;
	}

	//Spawn the enemy
	if(SpawnInterval <= 0)
	{
		if(ActiveSpawn < MaximumSpawn)
		{
		SpawnedEnemy = GetWorld()->SpawnActor<AEnemyFlyingAI>(EnemyToSpawn, GetActorLocation(), GetActorRotation());
		SpawnedEnemy->SpawnedHive = this;
		SpawnInterval = 5.0f;
		ActiveSpawn += 1;
		}
	}
}

