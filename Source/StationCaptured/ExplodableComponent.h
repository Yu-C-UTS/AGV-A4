// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "DamageableComponent.h"
#include "ExplodableComponent.generated.h"


UCLASS( ClassGroup=(Explodable), meta=(BlueprintSpawnableComponent) )
class STATIONCAPTURED_API UExplodableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExplodableComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float CurrentHealth;

	TArray<AActor*> OverllapingActors;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//Sphere Collider for Explode() Function
	// UPROPERTY(BlueprintReadWrite)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USphereComponent* SphereCollider;

	
	// UPROPERTY(EditAnywhere)
	// float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosiveDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosiveDamageRadius;

	// UFUNCTION(BlueprintCallable)
	// virtual void Damage(float DamageValue);

	UFUNCTION(BlueprintCallable)
	virtual void Explode();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEmptyDelegateSignature);
	UPROPERTY(BlueprintAssignable, Category = "Explodable")
	FEmptyDelegateSignature OnDeathExplode;

	
};
