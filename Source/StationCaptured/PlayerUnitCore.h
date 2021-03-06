// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitCore.h"
#include "Camera/CameraComponent.h"
#include "PlayerUnitCore.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API APlayerUnitCore : public AUnitCore
{
	GENERATED_BODY()
	
public:
	APlayerUnitCore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UCameraComponent* Camera;

public:
	UPROPERTY(VisibleAnywhere)
	float MaxSpeed;
	UPROPERTY(VisibleAnywhere)
	float Acceleration;

	UPROPERTY(BlueprintReadWrite)
	bool bIsBreaking;

private:
	float CurrentSpeed;

private:
	void Forward(float Value);
	void Strafe(float Value);
	void Up(float Value);
	void Pitch(float Value);
	void Yaw(float Value);
	void Roll(float Value);

	
	void BreakToggle();
	void BreakStart();
	void BreakEnd();
	//void Attack();

protected:
	UFUNCTION(Server,Reliable)
	void ServerMove(FVector NewLocation, FVector Velocity);
	UFUNCTION(Server, Reliable)
	void ServerRotate(FRotator NewRotation);
};
