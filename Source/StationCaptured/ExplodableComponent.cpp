// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodableComponent.h"
#include "Kismet/KismetSystemLibrary.h"
//#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UExplodableComponent::UExplodableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//MaxHealth = 50.0f;
	ExplosiveDamage = 80.0f;
	ExplosiveDamageRadius = 500.0f;
	// ...

}


// Called when the game starts
void UExplodableComponent::BeginPlay()
{
	Super::BeginPlay();
	// CurrentHealth = MaxHealth;
	// ...
	
}


// Called every frame
void UExplodableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// void UExplodableComponent::Damage(float DamageValue)
// {
// 	CurrentHealth -= DamageValue;
// 	if (CurrentHealth <= 0)
// 	{
// 		Explode();
// 	}
// }

void UExplodableComponent::Explode()
{
	// SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	// SphereCollider->SetSphereRadius(ExplosiveDamageRadius, true);
	
	// SphereCollider = ConstructObject<USphereComponent>(UStaticMeshComponent::StaticClass(), this, TEXT("SphereCollider");
	// if(SphereCollider)
	// {
	// SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	// SphereCollider->SetSphereRadius(ExplosiveDamageRadius, true);
    // SphereCollider->RegisterComponent();
    // SphereCollider->AttachTo(GetOwner()->GetRootComponent(), NAME_None);
	// }

	//EXPLODEEEE
	SphereCollider->GetOverlappingActors(OverllapingActors);
	for(int i = 0; i < OverllapingActors.Num(); i++)
	{
		if(OverllapingActors[i]->FindComponentByClass<UDamageableComponent>())
		{
			OverllapingActors[i]->FindComponentByClass<UDamageableComponent>()->Damage(ExplosiveDamage);
		}
	}
	GetWorld()->DestroyActor(GetOwner());
}

