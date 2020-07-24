// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "PickableBase.h"
#include "PickableWeapon.h"
#include "Engine/World.h"
#include "AIController.h"
#include "BrainComponent.h"

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	CreateAndAttachWeapon();
}

void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAICharacter::CreateAndAttachWeapon()
{
	FVector location = GetActorLocation();
	FRotator rotation = GetActorRotation();

	if (Shield != nullptr)
	{
		APickableBase* newShield = Cast<APickableBase>(GetWorld()->SpawnActor(Shield, &location, &rotation));
		newShield->AttachItemTo(GetMesh(), TEXT("DualWeaponPoint"));
	}
	if (Weapon != nullptr)
	{
		APickableWeapon* newWeapon = Cast<APickableWeapon>(GetWorld()->SpawnActor(Weapon, &location, &rotation));
		newWeapon->AttachItemTo(GetMesh(), TEXT("WeaponPoint"));
	}
}

void AAICharacter::TriggerAttack()
{
	Attack();
}

