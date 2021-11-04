// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UHealthComponent::Damage(float damageValue)
{
	CurrentHealth -= damageValue;

	if (CurrentHealth <= 0)
	{
		OnDeath();
	}
}

float UHealthComponent::GetCurrentHealthPercentage()
{
	return CurrentHealth/MaxHealth;
}
