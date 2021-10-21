// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Curves/CurveVector.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

///BASE FUNCTIONS
APlayerCharacter::APlayerCharacter()
{
	//TICK TOGGLE
	PrimaryActorTick.bCanEverTick = true;

	//CAMERA SETUP
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	//CHARMOVE SETUP
	Movement = GetCharacterMovement();
}

void APlayerCharacter::BeginPlay()
{
	//SUPER
	Super::BeginPlay();

	//SET PLAYER TO FUNCTION ON GROUND
	SetupGroundConditions();

	//RESET CAMERA ROLL
	currentCameraRoll = 0.0f;

	//REMOVE LATER
	Movement->MaxWalkSpeed = baseSpeed;
	Movement->MaxFlySpeed = baseSpeed;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	//SUPER
	Super::Tick(DeltaTime);

	//UPDATE CAMERA
	Camera->SetWorldRotation(FRotator(GetViewRotation().Pitch, GetViewRotation().Yaw, currentCameraRoll));
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind Actions to Controls
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Flip", IE_Pressed, this, &APlayerCharacter::HandleOrientation);

	//Bind Movement Input to Controls
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
}
///BASE FUNCTIONS

///MOVEMENT FUNCTIONS
void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::Turn(float Value)
{
	if (orientation == Normal)
	{
		AddControllerYawInput(Value);
	}
	else if (orientation == Flipped)
	{
		AddControllerYawInput(-Value);
	}
}