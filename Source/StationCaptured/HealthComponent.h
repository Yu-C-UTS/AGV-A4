// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableComponent.h"
#include "HealthComponent.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API UHealthComponent : public UDamageableComponent
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	float MaxHealth;

private:
	float CurrentHealth;

public:
	virtual void Damage(float damageValue) override;
	float GetCurrentHealthPercentage();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();
};
