// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	MaxHealth = 100;
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