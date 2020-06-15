// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("starting from player"));

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Mouse_X", this, &APlayerCharacter::Mouse_X);
	PlayerInputComponent->BindAxis("Mouse_Y", this, &APlayerCharacter::Mouse_Y);
}

void APlayerCharacter::MoveForward(float value)
{
	if (!bIsAlive)
		return;
	if(!bIsAttacking)
	{
		FRotator CamRot = GetControlRotation();
		CamRot.Pitch = 0.0f;
		FVector MoveDir = CamRot.Vector();

		GetCharacterMovement()->AddInputVector(MoveDir * value);
	}
}

void APlayerCharacter::MoveRight(float value)
{
}

void APlayerCharacter::Mouse_X(float value)
{
}

void APlayerCharacter::Mouse_Y(float value)
{
}

