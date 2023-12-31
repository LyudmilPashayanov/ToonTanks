// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	virtual void HandleDestruction();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Tank Properties", meta = (AllowPrivateAccess = true))
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Tank Properties", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Tank Properties", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Tank Properties", meta = (AllowPrivateAccess = true))
	USceneComponent* ProjectileSpawnComponent;
	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleDeathEffect;
	UPROPERTY(EditAnywhere, Category = "Sounds")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<class  UCameraShakeBase> DeathCameraShakeClass;

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> Projectile;
};
