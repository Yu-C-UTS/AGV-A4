// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapPiece.h"
#include "ConnectionPoint.h"
#include "ConnectableMapPiece.generated.h"

/**
 * 
 */
UCLASS()
class STATIONCAPTURED_API AConnectableMapPiece : public AMapPiece
{
	GENERATED_BODY()
	
public:
	AConnectableMapPiece();

public:
	virtual void Initialize() override;
	void ConnectAndRepositionMapPiece(UConnectionPoint* ConnectFrom, UConnectionPoint* ConnectTo);

	int Size;

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<UConnectionPoint*> ConnectionPoints;

public:
	TArray<UConnectionPoint*> GetConnectionPoints();
	TArray<UConnectionPoint*> GetOpenConnectionPoints();

};
