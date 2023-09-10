// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* actor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame(); // handled in the Blueprint event graph.

private:
	class ATank* PlayerTank;	
	float StartDelay = 3.f;
	int32 enemiesCount;
	void HandleGameStart();
	int32 GetEnemiesCount();
};
