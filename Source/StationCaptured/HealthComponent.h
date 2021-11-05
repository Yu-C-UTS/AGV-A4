// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableComponent.h"
#include "HealthComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Damagable), meta = (BlueprintSpawnableComponent))
class STATIONCAPTURED_API UHealthComponent : public UDamageableComponent
{
	GENERATED_BODY()
	
public:
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	float MaxHealth;

protected:
	float CurrentHealth;

public:
	virtual void Damage(float DamageValue) override;
	float GetCurrentHealthPercentage();

public:
	//UFUNCTION(BlueprintImplementableEvent)
	//void OnDeath();
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeath OnDeath;
};
