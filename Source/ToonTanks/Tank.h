// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"

#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleDestruction() override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input)
	class UInputMappingContext* PlayerMappingContext;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input)
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input)
	class UInputAction* TurnAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input)
	class UInputAction* FireAction;

	void TurnCallback(const FInputActionValue& Value);
	void MoveCallback(const FInputActionValue& Value);
	void FireCallback(const FInputActionValue& Value);
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	float TankSpeed=400;
	UPROPERTY(EditAnywhere)
	float TankTurnSpeed=400;

	class AToonTanksPlayerController* PlayerController;

	void SetupInputSystem();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
