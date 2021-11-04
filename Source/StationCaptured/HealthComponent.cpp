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
	CurrentHealth -= DamageValue;

	if (CurrentHealth <= 0)
	{
		OnDeath();
	}
}

float UHealthComponent::GetCurrentHealthPercentage()
{
	return FMath::Max(0.0f, CurrentHealth) / MaxHealth * 100;
}
