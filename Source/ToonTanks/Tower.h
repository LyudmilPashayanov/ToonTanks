// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class ATank* Tank;
	UPROPERTY(EditAnywhere)
	float TurretRange;

	FTimerHandle FireRateTimeHandler;
	float FireRate = 2.f;
	void CheckFireCondition();
	bool TankInRange();
};
