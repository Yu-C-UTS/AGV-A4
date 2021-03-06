// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldedHealthComponent.h"
#include "Net/UnrealNetwork.h"

UShieldedHealthComponent::UShieldedHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxShield = 100;
	ShieldRechargeRate = 20;
	ShieldRechargeCooldown = 5;
	bOverflowShieldDamageToHealth = false;
}

void UShieldedHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentShield = MaxShield;
}

void UShieldedHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	TickRechargeShield(DeltaTime);
	
}

void UShieldedHealthComponent::TickRechargeShield(float DeltaTime)
{
	//Check if Shield recharge is needed
	if (CurrentShield >= MaxShield)
	{
		CurrentRechargeCooldown = ShieldRechargeCooldown;
		return;
	}

	//do cooldown check
	if (CurrentRechargeCooldown > 0)
	{
		CurrentRechargeCooldown -= DeltaTime;
		return;
	}

	//RechargeShield
	CurrentShield += ShieldRechargeRate * DeltaTime;
}

void UShieldedHealthComponent::Damage(float DamageValue)
{
	CurrentRechargeCooldown = ShieldRechargeCooldown;

	float ActiveDamage = DamageValue;

	if (CurrentShield > 0)
	{
		ActiveDamage -= CurrentShield;
		CurrentShield -= DamageValue;

		if (ActiveDamage < 0 || !bOverflowShieldDamageToHealth)
		{
			return;
		}
	}

	//Do damage to health
	Super::Damage(ActiveDamage);
}

float UShieldedHealthComponent::GetCurrentShieldPercentage()
{
	return FMath::Max(0.0f, CurrentShield) / MaxShield * 100;
}

void UShieldedHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UShieldedHealthComponent, CurrentShield);
}

