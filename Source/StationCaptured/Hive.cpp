// Fill out your copyright notice in the Description page of Project Settings.


#include "Hive.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"

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

	SpawnCooldown = SpawnInterval;
}

// Called every frame
void AHive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasAuthority())
	{
		//Don't bother ticking the rest if this is not the server
		return;
	}

	ChildUnitCheck();
	TickSpawnUnit(DeltaTime);
	ChildUnitGetAlly();
}

void AHive::TickSpawnUnit(float DeltaTime)
{
	AEnemyFlyingAI* SpawnedEnemy;
	//Countdown for spawn
	if(SpawnCooldown > 0)
	{
		SpawnCooldown -= DeltaTime;
		return;
	}
	FVector Test (500,500,500);
	//Spawn the enemy
	if(ActiveChildUnits.Num() < MaximumSpawn)
	{ //SpawnPointOverride ? SpawnPointOverride->GetComponentLocation() : GetActorLocation()
		SpawnedEnemy = GetWorld()->SpawnActor<AEnemyFlyingAI>(EnemyToSpawn, SpawnPointOverride->GetComponentLocation(), GetActorRotation());
		if (!SpawnedEnemy)
		{
			//Spawn failed, return and retry next tick
			return;
		}

		SpawnedEnemy->SpawnedHive = this;
		ActiveChildUnits.Add(SpawnedEnemy);
		SpawnCooldown = SpawnInterval;
	}
}


void AHive::ChildUnitCheck()
{
	if (ActiveChildUnits.Num() <= 0)
	{
		return;
	}
	for (int i = ActiveChildUnits.Num() - 1; i >= 0; i--)
	{
		if (!IsValid(ActiveChildUnits[i]))
		{
			ActiveChildUnits.RemoveAt(i);
		}
	}
}

void AHive::ChildUnitGetAlly()
{
	for (int i = 0; i < ActiveChildUnits.Num(); i++)
	{
		if(ActiveChildUnits[i])
		{
			for (int j = 0; j < ActiveChildUnits.Num(); j++)
			{
				if(ActiveChildUnits[j]->CanSeePlayer())
				{
					ActiveChildUnits[i]->Ally = ActiveChildUnits[j];
				}
			}
		}
	}
}
	
	//for (AEnemyFlyingAI* ChildUnit : ActiveChildUnits)
	//{
	//	if (!ChildUnit)
	//	{
	//		ActiveChildUnits.Remove(ChildUnit);
	//	}
	//}


