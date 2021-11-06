// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	MaxHealth = 100;
	SetIsReplicated(true);
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UHealthComponent::Damage(float DamageValue)
{
	if(CurrentHealth <= 0)
	{
		return;
	}
	CurrentHealth -= DamageValue;
	if (OnHealthDamage.IsBound())
	{
		OnHealthDamage.Broadcast(DamageValue);
	}

	if (CurrentHealth <= 0)
	{
		if (OnDeath.IsBound())
		{
			OnDeath.Broadcast();
		}
	}
}

float UHealthComponent::GetCurrentHealthPercentage()
{
	return FMath::Max(0.0f, CurrentHealth) / MaxHealth * 100;
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UHealthComponent, CurrentHealth);
}
