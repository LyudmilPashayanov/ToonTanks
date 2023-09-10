// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimeHandler, this, &ATower::CheckFireCondition,FireRate,true); // looping timer which will be called every 'FireRate' seconds.
}

void ATower::CheckFireCondition()
{
	if (TankInRange())
	{
		Fire();
	}
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(TankInRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

bool ATower::TankInRange()
{
	if (Tank)
	{
		FVector TankLocation = Tank->GetActorLocation();
		float DistanceToTank = FVector::Distance(TankLocation, GetActorLocation());
		if (TurretRange > DistanceToTank)
		{
			return true;
		}
		return false;
	}
	return false;
}
