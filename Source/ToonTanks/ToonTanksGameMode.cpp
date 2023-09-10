// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BasePawn.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"

void AToonTanksGameMode::ActorDied(AActor* deadActor)
{
	if(ABasePawn* baseDeadPawn = Cast<ABasePawn>(deadActor))
	{
		baseDeadPawn->HandleDestruction();
	}
}

// Called when the game starts
void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	if(AToonTanksPlayerController* ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0)))
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);
		FTimerHandle TimerHandle;
		StartGame();
		// Delegate which can take function parameters and be executed on the end of a Timer;
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject
		(ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true);
		
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, StartDelay, true); // looping timer which will be called every 'FireRate' seconds.
	}
}
