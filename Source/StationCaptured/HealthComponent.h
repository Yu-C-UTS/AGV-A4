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
	UPROPERTY(BlueprintReadWrite)
	float CurrentHealth;

public:
	virtual void Damage(float DamageValue) override;
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealthPercentage();

public:
	//UFUNCTION(BlueprintImplementableEvent)
	//void OnDeath();
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEmptyDelegateSignature);
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FEmptyDelegateSignature OnDeath;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOneFloatDelegateSignature, float, Value);
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOneFloatDelegateSignature OnHealthDamage;
};
