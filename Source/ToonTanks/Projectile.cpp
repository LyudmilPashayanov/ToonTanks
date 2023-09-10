// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = ProjectileMeshComponent;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System component"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit); // setting callback, so that OnComponentHit invokes, we callback our OnHit function.
	if(LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if(MyOwner)
	{
		auto MyOwnerInstigator = MyOwner->GetInstigatorController();
		auto DamageTypeClass = UDamageType::StaticClass();
		if(OtherActor && OtherActor != this && OtherActor != MyOwner)
		{
			if (HitParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorLocation(), GetActorRotation());
			}
			if (HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, HitSound, OtherActor->GetActorLocation());
			}
			if (HitCameraShakeClass)
			{
				GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
			}

			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, MyOwner, DamageTypeClass);
		}
	}	
	Destroy();
}

