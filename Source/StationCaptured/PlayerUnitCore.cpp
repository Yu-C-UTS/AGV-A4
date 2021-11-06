// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUnitCore.h"
#include "Net/UnrealNetwork.h"
#include "Engine/GameEngine.h"
#include "Engine/World.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/InputComponent.h"

APlayerUnitCore::APlayerUnitCore()
{
	PrimaryActorTick.bCanEverTick = true;

	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	MaxSpeed = 1000.0f;
	Acceleration = 600.0f;
	bIsBreaking = false;
}

void APlayerUnitCore::BeginPlay()
{
	Super::BeginPlay();

	Camera = FindComponentByClass<UCameraComponent>();

	UFloatingPawnMovement* floatingPawnMovement = FindComponentByClass<UFloatingPawnMovement>();
	floatingPawnMovement->MaxSpeed = MaxSpeed;
	floatingPawnMovement->Acceleration = Acceleration;
	floatingPawnMovement->Deceleration = 0;
	bIsBreaking = false;
}

void APlayerUnitCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerUnitCore::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &APlayerUnitCore::Forward);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &APlayerUnitCore::Strafe);
	PlayerInputComponent->BindAxis(TEXT("Up"), this, &APlayerUnitCore::Up);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &APlayerUnitCore::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &APlayerUnitCore::Roll);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &APlayerUnitCore::Yaw);

	///Breaking:
	//Hold to break
	//PlayerInputComponent->BindAction(TEXT("Break"), EInputEvent::IE_Pressed, this, &APlayerUnitCore::BreakStart);
	//PlayerInputComponent->BindAction(TEXT("Break"), EInputEvent::IE_Released, this, &APlayerUnitCore::BreakEnd);
	//Toggle Break
	PlayerInputComponent->BindAction(TEXT("Break"), EInputEvent::IE_Released, this, &APlayerUnitCore::BreakToggle);
	//PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayerUnitCore::Attack);
}

void APlayerUnitCore::Forward(float Value)
{
	//if (FMath::IsNearlyZero(Value))
	//{
	//	return;
	//}
	//CurrentSpeed = FMath::Clamp(CurrentSpeed + Acceleration * Value * GetWorld()->GetDeltaSeconds(), -MaxSpeed, MaxSpeed);
	AddMovementInput(GetActorForwardVector(), Value);
	ServerMove(GetActorLocation());
	//GetMovementComponent()->AddInputVector(GetActorForwardVector() * Value);
}

void APlayerUnitCore::Strafe(float Value)
{
	//if (FMath::IsNearlyZero(Value))
	//{
	//	return;
	//}
	//CurrentSpeed = FMath::Clamp(CurrentSpeed + Acceleration * Value * GetWorld()->GetDeltaSeconds(), -MaxSpeed, MaxSpeed);
	AddMovementInput(GetActorRightVector(), Value);
	ServerMove(GetActorLocation());
	//GetMovementComponent()->AddInputVector(GetActorRightVector() * Value);
}

void APlayerUnitCore::Up(float Value)
{
	//if (FMath::IsNearlyZero(Value))
	//{
	//	return;
	//}
	//CurrentSpeed = FMath::Clamp(CurrentSpeed + Acceleration * Value * GetWorld()->GetDeltaSeconds(), -MaxSpeed, MaxSpeed);
	AddMovementInput(GetActorUpVector(), Value);
	ServerMove(GetActorLocation());
	//GetMovementComponent()->AddInputVector(GetActorUpVector() * Value);
}

void APlayerUnitCore::Pitch(float Value)
{
	AddActorLocalRotation(FRotator(Value, 0.0f, 0.0f));
	ServerRotate(GetActorRotation());
}

void APlayerUnitCore::Yaw(float Value)
{
	AddActorLocalRotation(FRotator(0.0f, Value, 0.0f));
	ServerRotate(GetActorRotation());
}

void APlayerUnitCore::Roll(float Value)
{
	AddActorLocalRotation(FRotator(0.0f, 0.0f, Value));
	ServerRotate(GetActorRotation());
}

void APlayerUnitCore::BreakToggle()
{
	if (bIsBreaking)
	{
		BreakEnd();
	}
	else 
	{
		BreakStart();
	}
}

void APlayerUnitCore::BreakStart()
{
	UFloatingPawnMovement* floatingPawnMovement = FindComponentByClass<UFloatingPawnMovement>();
	floatingPawnMovement->Deceleration = Acceleration;
	bIsBreaking = true;
}

void APlayerUnitCore::BreakEnd()
{
	UFloatingPawnMovement* floatingPawnMovement = FindComponentByClass<UFloatingPawnMovement>();
	floatingPawnMovement->Deceleration = 0;
	bIsBreaking = false;
}

void APlayerUnitCore::ServerMove_Implementation(FVector NewLocation)
{
	SetActorLocation(NewLocation);
}

void APlayerUnitCore::ServerRotate_Implementation(FRotator NewRotation)
{
	SetActorRotation(NewRotation);
}

// void APlayerUnitCore::Attack()
// {

// }
