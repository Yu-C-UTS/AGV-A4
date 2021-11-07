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

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyFlyingAI> EnemyToSpawn;
	UPROPERTY(EditAnywhere)
	float SpawnInterval;
	UPROPERTY(EditAnywhere)
	int MaximumSpawn;
	UPROPERTY(BlueprintReadWrite)
	USceneComponent* SpawnPointOverride;
	
private:
	float SpawnCooldown;

	UPROPERTY(VisibleAnywhere)
	TArray<AEnemyFlyingAI*> ActiveChildUnits;

	void TickSpawnUnit(float DeltaSeconds);
	void ChildUnitCheck();
	void ChildUnitGetAlly();
};
