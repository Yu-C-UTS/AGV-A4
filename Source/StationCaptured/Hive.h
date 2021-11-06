// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFlyingAI.h"
#include "Hive.generated.h"

UCLASS()
class STATIONCAPTURED_API AHive : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float SpawnInterval;
	
	UPROPERTY(EditAnywhere)
	int MaximumSpawn;

	UPROPERTY(BlueprintReadWrite)
	int ActiveSpawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyFlyingAI> EnemyToSpawn;

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy(float DeltaSeconds);


};
