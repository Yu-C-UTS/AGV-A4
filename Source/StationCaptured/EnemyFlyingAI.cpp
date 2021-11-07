// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFlyingAI.h"
#include "Engine/World.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"

AEnemyFlyingAI::AEnemyFlyingAI()
{
	PrimaryActorTick.bCanEverTick = true;
	bCanSeePlayer = false;
	bIsRally = false;
}

void AEnemyFlyingAI::BeginPlay()
{
	Super::BeginPlay();
	//GetRandomLocations();
	
	CurrentState = AIState::Scan;
}


// Called every frame
void AEnemyFlyingAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// ...
	FHitResult Hit(ForceInit);
	FCollisionQueryParams Params = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
	switch(CurrentState)
	{
		case AIState::Scan:
		if(GetActorRotation() == ScanDirection)
		{
			//Rayscan Forward
			bool OutHit = DoTrace(&Hit, &Params);
			if(!OutHit)
			{
				//Ray End Point
				PatrolToLocation = GetActorLocation() + (GetActorRotation().Vector() * MaxTraceDistance);
			}

			// Check for distance between the AI and its end point if far enough
			if(FVector::Dist(PatrolToLocation, GetActorLocation()) > ObstacleAvoidDistance)
			{
				CurrentState = AIState::Patrol;
				break;
			}
		}
	}
}

//FVector::Dist returns the Distance between 2 vector points

bool AEnemyFlyingAI::DoTrace(FHitResult* Hit, FCollisionQueryParams* Params)
{
	FVector Loc = GetActorLocation();
	FRotator Rot = GetActorRotation();
	FVector Start = Loc; 
	FVector End = Loc + (Rot.Vector() * MaxTraceDistance);
	Params->bTraceComplex = true;
	//Params->bTraceAsyncScene  = true;
	Params->bReturnPhysicalMaterial = true;
	bool Traced = GetWorld()->LineTraceSingleByChannel
	(
		*Hit, Start, End, ECC_Visibility, *Params
	);
	return Traced;
}

void AEnemyFlyingAI::GetAllies()
{
}

void AEnemyFlyingAI::GatherAboveHive()
{
	if(SpawnedHive)
	{
	FVector LocationAwayFromHive(0,0,800.0f);
	FVector DistanceToHive = (SpawnedHive->GetActorLocation() + LocationAwayFromHive) - GetActorLocation();
	AddMovementInput(DistanceToHive,1.0f,true);
	}
}

// void AEnemyFlyingAI::GetRandomLocations()
// {
// 	for(int i = 0; i < 1000; i++)
// 	{	//Generate 1000 random locations across the map
// 		RandomLocations[i] = {FMath::FRandRange(20000.0f, 20000.0f), FMath::FRandRange(20000.0f, 20000.0f), FMath::FRandRange(20000.0f, 20000.0f)};
// 	}
// }


void AEnemyFlyingAI::Patrol()
{
	//Generate a Random Location around the Hive
	//FVector RandomLoc = SpawnedHive->GetActorLocation();
 	// RandomLoc.X = FMath::FRandRange(-10, 10);
 	// RandomLoc.Y = FMath::FRandRange(-10, 10);
 	// RandomLoc.Z = FMath::FRandRange(-10, 10);

	// //Get the Direction to the RandomLoc
	// for(int i = 0; i < RandomLocations.Num(); i++)
	// {	//Get random locations every tick 
	// FVector DistanceToRandomLocation = RandomLocations[FMath::FRandRange(0, RandomLocations.Num()-1)] - GetActorLocation();
	// // Move towards random locations
	// AddMovementInput(DistanceToRandomLocation, 1.0f, true);
	// }

}

bool AEnemyFlyingAI::CanSeePlayer()
{
	if(UnitToChase)
	{
		if (FVector::Dist(UnitToChase->GetActorLocation(), GetActorLocation()) > FollowingDistance)
		{
		bCanSeePlayer = false;
		}
		else if (FVector::Dist(UnitToChase->GetActorLocation(), GetActorLocation()) < SightDistance)
		{
		bCanSeePlayer = true;
		}
	}
	return bCanSeePlayer;
}

//LocationAwayFromUnit determines how far away should the AI be from the player, with height in Z and DistanceAway with X and Y
//DistanceToUnit returns the vector point straight to the player

void AEnemyFlyingAI::ChasePlayer()
{
	if(UnitToChase)
	{
	FVector LocationAwayFromUnit(FGenericPlatformMath::FRand() * DistanceAway, FGenericPlatformMath::FRand() * DistanceAway, FGenericPlatformMath::FRand() * Height);
	FVector DistanceToUnit = (UnitToChase->GetActorLocation() + LocationAwayFromUnit) - GetActorLocation();
	AddMovementInput(DistanceToUnit,1.0f,true);
	}
}

//PlayerLoc returns the rotation to look at the player

void AEnemyFlyingAI::LookAtPlayer()
{
	if(UnitToChase)
	{
	FRotator PlayerLoc = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UnitToChase->GetActorLocation());
	FRotator Rotation = FMath::RInterpTo(GetActorRotation(), PlayerLoc, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 20.0);
	SetActorRotation(Rotation);
	}
}

//SpawnRot returns the rotation to look at the player
// void AEnemyFlyingAI::Fire()
// {
// 	FRotator SpawnRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UnitToChase->GetActorLocation());
// 	if (FVector::Dist(UnitToChase->GetActorLocation(), GetActorLocation()) < 800.0f)
// 	{
// 		if (bCanSeePlayer) 
// 		{
// 			GetWorld()->SpawnActor<AActor>(Bullet, GetActorLocation(), SpawnRot);
// 		}
// 	}
// }

//SpawnedHive is the Hive reference Actor
void AEnemyFlyingAI::TeleportToHive()
{
	if(SpawnedHive)
	{
		TeleportTo(SpawnedHive->GetActorLocation(), SpawnedHive->GetActorRotation());
	}
}

//return bIsRally = true if Ally can see the player
bool AEnemyFlyingAI::IsRally()
{
	if(Ally)
	{
		if (Ally->CanSeePlayer())
		{
		bIsRally = true;
		}
	}
	else bIsRally = false;
	return bIsRally;
}

void AEnemyFlyingAI::GatherWithAlly()
{
	{
		if(Ally)
		{
		CanSeePlayer();
		// SetActorLocation(Ally->GetActorLocation() + (-100.0f,-100.0f,-100.0f));
		// SetActorRotation(Ally->GetActorRotation());
		//bIsRally = false;
		FVector DistanceToAlly = Ally->GetActorLocation() - GetActorLocation();
		AddMovementInput(DistanceToAlly,1.0f,true);
		//bIsRally = false;
		}
		else GatherAboveHive();
		bIsRally = false;
	}
}

// Will be used then teleport to Hive
// void AEnemyFlyingAI::Healing()
// {
// 	if (Health < 100)
// 	{
// 		Health += 1;
// 	}
// }

// void AEnemyFlyingAI::TakeDamage()
// {

// }

// void AEnemyFlyingAI::DealDamage()
// {
	
// }

// void AEnemyFlyingAI::Dead()
// {
// 	if (Health < 0.01f)
// 	{
// 		bIsRally = false;
// 		bCanSeePlayer = false;
// 		GetWorld()->DestroyActor(this);
// 	}
// }




//void AEnemyFlyingAI::AvoidObstacle()
//{	
//}

