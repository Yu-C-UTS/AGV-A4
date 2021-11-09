// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectableMapPiece.h"

AConnectableMapPiece::AConnectableMapPiece()
{
	Size = 0;
}

void AConnectableMapPiece::Initialize()
{
	for (UActorComponent* Component : this->GetComponents())
	{
		if (Component->IsA<UConnectionPoint>())
		{
			ConnectionPoints.Add(Cast<UConnectionPoint>(Component));
		}
	}
}

void AConnectableMapPiece::ConnectAndRepositionMapPiece(UConnectionPoint* ConnectFrom, UConnectionPoint* ConnectTo)
{
	if (!ConnectionPoints.Contains(ConnectFrom))
	{
		UE_LOG(LogTemp, Warning, TEXT("ConnectFrom connection component (%s) does not belong to this map piece (%s)"), ConnectFrom, this);
	}

	//
	//Rotate the piece so that the connection point faces the correct direction
	//
	//UE_LOG(LogTemp, Display, TEXT("Target ConnectFrom Rotation: %s"), *(TargetConnectFromRotation).ToString());
	//UE_LOG(LogTemp, Display, TEXT("Relative Rotation: %s"), *(RootComponent->GetComponentRotation() - ConnectFrom->GetComponentRotation()).ToString());
	//UE_LOG(LogTemp, Display, TEXT("Current Rotation: %s"), *(RootComponent->GetComponentRotation()).ToString());
	//UE_LOG(LogTemp, Display, TEXT("ConnectFrom Rotation: %s"), *(ConnectFrom->GetComponentRotation()).ToString());

	FRotator ConnectToInvertRotator = (ConnectTo->GetComponentRotation().Vector() * -1).ToOrientationRotator();
	FRotator ConnectFromRotator = ConnectFrom->GetComponentRotation().Vector().ToOrientationRotator();
	if (FMath::IsNearlyEqual(FMath::Abs(ConnectToInvertRotator.Pitch), 90.0f, 0.05f))
	{
		ConnectToInvertRotator.Yaw = 0;
	}
	if (FMath::IsNearlyEqual(FMath::Abs(ConnectFromRotator.Pitch), 90.0f, 0.05f))
	{
		ConnectFromRotator.Yaw = 0;
	}
	FRotator Rotation = ConnectToInvertRotator - ConnectFromRotator;
	if (FMath::IsNearlyEqual(FMath::Abs(Rotation.Pitch), 90.0f, 0.05f))
	{
		Rotation.Yaw -= 90;
	}
	//UE_LOG(LogTemp, Display, TEXT("Connect to Inv: %s"), *(ConnectToInvertRotator.ToString()));
	//UE_LOG(LogTemp, Display, TEXT("Connect From: %s"), *(ConnectFromRotator.ToString()));
	//UE_LOG(LogTemp, Display, TEXT("Rotation: %s"), *(Rotation).ToString());

	this->RootComponent->AddWorldRotation(Rotation);

	FRotator Remaining;
	for (int i = 0; i < 10; i++)
	{
		Remaining = (ConnectTo->GetComponentRotation().Vector() * -1).ToOrientationRotator() - (ConnectFrom->GetComponentRotation().Vector().ToOrientationRotator());
		//UE_LOG(LogTemp, Warning, TEXT("Remaining No. %i: %s"), i, *(Remaining).ToString());
		//Remaining.Yaw -= (FMath::FloorToInt(Remaining.Yaw) % 90);
		if (FMath::IsNearlyEqual(FMath::Abs(Remaining.Pitch), 90.0f, 0.05f))
		{
			Remaining.Pitch *= -1;
		}
		//UE_LOG(LogTemp, Display, TEXT("Adding Rotation: %s"), *(Remaining).ToString());
		this->RootComponent->AddWorldRotation(Remaining);
		//UE_LOG(LogTemp, Display, TEXT("Result dot product: %f"), FVector::DotProduct((ConnectTo->GetComponentRotation().Vector() * -1), ConnectFrom->GetComponentRotation().Vector()));
		if (FVector::DotProduct((ConnectTo->GetComponentRotation().Vector() * -1), ConnectFrom->GetComponentRotation().Vector()) > 0.95)
		{
			break;
		}
	}
	/*DOES NOT WORK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for (int i = 0; i < 6; i++)
	{
		if (i % 2 == 0)
		{
			this->AddActorWorldRotation(FRotator(90, 0, 0));
		}
		else
		{
			this->AddActorWorldRotation(FRotator(0, 0, 90));
		}
		UE_LOG(LogTemp, Display, TEXT("Facing %i: %s"), i, *(.ToString()));
		UE_LOG(LogTemp, Display, TEXT("Result dot product %i: %f"), i, FVector::DotProduct(ConnectTo->GetComponentRotation().Vector(), ConnectFrom->GetComponentRotation().Vector()));
		if (FMath::IsNearlyEqual(FVector::DotProduct(ConnectTo->GetComponentRotation().Vector(), ConnectFrom->GetComponentRotation().Vector()), -1.0f, 0.05f))
		{
			break;
		}
	}*/

	//Move map piece into correct position
	this->SetActorLocation(ConnectTo->GetComponentLocation());
	this->AddActorWorldOffset(ConnectTo->GetComponentLocation() - ConnectFrom->GetComponentLocation());

	//UE_LOG(LogTemp, Display, TEXT("Connect from: %s"), *(ConnectFrom->GetComponentRotation().Vector()).ToString());

	//UE_LOG(LogTemp, Display, TEXT("Connect from: %s"), *(ConnectFrom->GetComponentLocation().ToString()));
	//UE_LOG(LogTemp, Display, TEXT("Connect to: %s"), *(ConnectTo->GetComponentLocation().ToString()));

	ConnectTo->bIsConnected = true;
	ConnectFrom->bIsConnected = true;
}

TArray<UConnectionPoint*> AConnectableMapPiece::GetConnectionPoints()
{
	return ConnectionPoints;
}

TArray<UConnectionPoint*> AConnectableMapPiece::GetOpenConnectionPoints()
{
	TArray<class UConnectionPoint*> OpenConnections;
	for (class UConnectionPoint* Connection : ConnectionPoints)
	{
		if (!Connection->bIsConnected)
		{
			OpenConnections.Add(Connection);
		}
	}
	return OpenConnections;
}
