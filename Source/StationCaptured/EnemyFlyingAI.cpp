// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFlyingAI.h"
#include "Engine/World.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"

//AEnemyFlyingAI::AEnemyFlyingAI()
//{
//	PrimaryActorTick.bCanEverTick = true;
//}

//FVector::Dist returns the Distance between 2 vector points

void AEnemyFlyingAI::GetAnotherPlayer()
{
	if(UnitToChase == nullptr)
	{
	}
}

void AEnemyFlyingAI::Patrol()
{
	if(SpawnedHive)
	{
	FVector LocationAwayFromHive(FGenericPlatformMath::FRand() * (-DistanceAway), FGenericPlatformMath::FRand() * (-DistanceAway), 350.0f);
	FVector DistanceToHive = (SpawnedHive->GetActorLocation() + LocationAwayFromHive) - GetActorLocation();
	AddMovementInput(DistanceToHive);
	}
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
	AddMovementInput(DistanceToUnit);
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
void AEnemyFlyingAI::Fire()
{
	FRotator SpawnRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UnitToChase->GetActorLocation());
	if (FVector::Dist(UnitToChase->GetActorLocation(), GetActorLocation()) < 800.0f)
	{
		if (bCanSeePlayer) 
		{
			GetWorld()->SpawnActor<AActor>(Bullet, GetActorLocation(), SpawnRot);
		}
	}
}

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

void AEnemyFlyingAI::TeleportToAlly()
{
	{
		if(Ally)
		{
		SetActorLocation(Ally->GetActorLocation() + (-100.0f,-100.0f,-100.0f));
		SetActorRotation(Ally->GetActorRotation());
		bIsRally = false;
		}
		else TeleportToHive();
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

