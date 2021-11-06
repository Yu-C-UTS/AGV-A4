// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "ShieldedHealthComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Damagable), meta = (BlueprintSpawnableComponent))
class STATIONCAPTURED_API UShieldedHealthComponent : public UHealthComponent
{
	GENERATED_BODY()
	
public:
	UShieldedHealthComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere)
	float MaxShield;
	UPROPERTY(EditAnywhere)
	float ShieldRechargeRate;
	UPROPERTY(EditAnywhere)
	float ShieldRechargeCooldown;
	UPROPERTY(EditAnywhere)
	bool bOverflowShieldDamageToHealth;

protected:
	UPROPERTY(Replicated)
	float CurrentShield;
	float CurrentRechargeCooldown;
	void TickRechargeShield(float DeltaTime);

public:
	virtual void Damage(float DamageValue) override;
	UFUNCTION(BlueprintCallable)
	float GetCurrentShieldPercentage();

	UFUNCTION(BlueprintImplementableEvent)
	void OnShieldBreak();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
