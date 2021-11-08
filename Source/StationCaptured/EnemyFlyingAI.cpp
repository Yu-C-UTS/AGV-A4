// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFlyingAI.h"
#include "Engine/World.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h"
//#include "Math/Vector.h"

AEnemyFlyingAI::AEnemyFlyingAI()
{
	PrimaryActorTick.bCanEverTick = true;
	bCanSeePlayer = false;
	bIsRally = false;
	CurrentState = AIState::Scan;
	Params = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
}

void AEnemyFlyingAI::BeginPlay()
{
	Super::BeginPlay();
	//GetRandomLocations();
	
}


// Called every frame
void AEnemyFlyingAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// ...
	
}

//FVector::Dist returns the Distance between 2 vector points

bool AEnemyFlyingAI::DoTrace(FHitResult TheHit) //FHitResult* TheHit, FCollisionQueryParams* TheParams
{
	const FName TraceTag("AITraceTag");
	GetWorld()->DebugDrawTraceTag = TraceTag;
	FVector Loc = GetActorLocation();
	FRotator Rot = GetActorRotation(); //Rot.Vector()
	FVector Start = Loc; 
	FVector End = Loc + (GetActorForwardVector() * MaxTraceDistance);
	// TheParams->bTraceComplex = true;
	// //Params->bTraceAsyncScene  = true;
	// TheParams->bReturnPhysicalMaterial = true;
	// TheParams->TraceTag = TraceTag;
	TArray<AActor*> ToIgnore;
	bool Traced = UKismetSystemLibrary::SphereTraceSingle
	(
		this, Start, End, 20.0f, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, ToIgnore, EDrawDebugTrace::ForOneFrame, TheHit, true 
	);
	// bool Traced = GetWorld()->LineTraceSingleByChannel
	// (
	// 	*TheHit, Start, End, ECC_Visibility, *TheParams
	// );
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
	FHitResult Hit(ForceInit);
	TArray<AActor*> ToIgnore;
	ToIgnore.Add(GetOwner());
	FVector Start = GetActorLocation(); 
	FVector End = GetActorLocation() + (GetActorForwardVector() * MaxTraceDistance);
	switch(CurrentState)
	{
		case AIState::Scan:

		//Slowly rotate and face towards scan direction
		UE_LOG(LogTemp, Warning, TEXT("Rotating, From: %s, To: %s, Current: %s"), *OldRotation.ToString(), *ScanDirection.ToString(), *GetActorRotation().ToString());
		RotationLerp = FMath::Clamp(RotationLerp + (GetWorld()->DeltaTimeSeconds / 2), 0.0f, 1.0f);
		SetActorRotation(FQuat::Slerp(OldRotation.Quaternion(), ScanDirection.Quaternion(), RotationLerp));
		//RotateToScanDirection = FMath::RInterpTo(GetActorRotation(), ScanDirection, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0.5);
		//SetActorRotation(RotateToScanDirection);

		//If unit has completed rotation, plan to rotate to look at a new direction
		if (FMath::IsNearlyEqual(FVector::DotProduct(GetActorForwardVector(), ScanDirection.Vector()), 1.0f, 0.05f))
		{
			OldRotation = GetActorRotation();
			RotationLerp = 0;
			ScanDirection = UKismetMathLibrary::RandomRotator();
			UE_LOG(LogTemp, Warning, TEXT("New Rotation"));

			//Rayscan Forward
			// bool Trace = DoTrace(Hit);
			UKismetSystemLibrary::SphereTraceSingle
			(
				this, Start, End, 20.0f, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, ToIgnore, EDrawDebugTrace::ForDuration, Hit, true 
			);
			//UE_LOG(LogTemp, Warning, TEXT("Tracing"));

			//If raycast hit something, don't move forward
			if(Hit.bBlockingHit)
			{
				break;
			}

			//If the forward direction is clear and unit should move forward
			PatrolToLocation = End;
			CurrentState = AIState::Patrol;
				//break;
		}

		break; //End Case

		case AIState::Patrol:
		//Move towards new patrol point
		AddMovementInput(GetActorForwardVector(), 1.0f, true);
		if(FVector::Dist(PatrolToLocation, GetActorLocation()) <= ObstacleAvoidDistance)
		{
			CurrentState = AIState::Scan;
		}
		break;
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

