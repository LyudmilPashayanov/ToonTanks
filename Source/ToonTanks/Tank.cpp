// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if(EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this, &ATank::Move);
		EnhancedInputComponent->BindAction(TurnAction,ETriggerEvent::Triggered,this, &ATank::Turn);
	}
}

// If I want to make simultanously pressed A and D to cancel each other, I have to split this function to TurnLeft and TurnRight and use a shared FRotator for turning.

void ATank::Turn(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();

	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this); // Could also use the Modifier "multiply by Delta time" in the Input Action options
	float DeltaYaw = AxisValue * deltaTime * TankTurnSpeed;
	FRotator deltaRotation = FRotator::ZeroRotator;
	deltaRotation.Yaw = DeltaYaw;
	AddActorLocalRotation(deltaRotation,true);
}

// If I want to make simultanously pressed W and S to cancel each other, I have to split this function to MoveForward and MoveBackwards and use a shared FVector for moving.
void ATank::Move(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();

	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this); // Could also use the Modifier "multiply by Delta time" in the Input Action options
	float XDeltaSpeed = AxisValue * deltaTime * TankSpeed;
	FVector deltaMove{XDeltaSpeed, 0, 0};
	AddActorLocalOffset(deltaMove,true);
}
