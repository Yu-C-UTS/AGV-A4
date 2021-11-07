// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerUnitCore.h"
#include "UnitCore.h"
#include "EnemyFlyingAI.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API AEnemyFlyingAI : public AUnitCore
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AEnemyFlyingAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BluePrintReadWrite)
	bool bCanSeePlayer;

	UPROPERTY(BluePrintReadWrite)
	bool bIsRally;

	UPROPERTY(EditAnywhere)
	float Height;

	UPROPERTY(EditAnywhere)
	float DistanceAway;

	// UPROPERTY(EditAnywhere, BluePrintReadWrite)
	// float Damage;

	// UPROPERTY(EditAnywhere, BluePrintReadWrite)
	// float Health = 100.0f;

	// UPROPERTY(EditAnywhere)
	// int32 MaxHealth;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	APlayerUnitCore* UnitToChase;

	// UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	// TSubclassOf<AActor> Bullet;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	AActor* SpawnedHive;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	AEnemyFlyingAI* Ally;

	UFUNCTION(BlueprintCallable)
	bool CanSeePlayer();

private:
	const float FollowingDistance = 3000.0f;
	const float SightDistance = 1500.0f;


	UFUNCTION(BlueprintCallable)
	void GetAllies();

	UFUNCTION(BlueprintCallable)
	void GatherAboveHive();

	UFUNCTION(BlueprintCallable)
	void Patrol();

	UFUNCTION(BlueprintCallable)
	void ChasePlayer();

	UFUNCTION(BlueprintCallable)
	void LookAtPlayer();

	// UFUNCTION(BlueprintCallable)
	// void Fire();

	UFUNCTION(BlueprintCallable)
	void TeleportToHive();

	UFUNCTION(BlueprintCallable)
	bool IsRally();

	UFUNCTION(BlueprintCallable)
	void GatherWithAlly();

	// UFUNCTION(BlueprintCallable)
	// void Healing();

	// UFUNCTION(BlueprintCallable)
	// void TakeDamage();

	// UFUNCTION(BlueprintCallable)
	// void DealDamage();

	// UFUNCTION(BlueprintCallable)
	// void Dead();



//	UFUNCTION(BlueprintCallable)
//	void AvoidObstacle();
};
