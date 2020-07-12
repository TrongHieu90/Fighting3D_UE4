// Fill out your copyright notice in the Description page of Project Settings.
#include "ArenaCharacter.h"
#include "PickableWeapon.h"
#include "PickableBase.h"
#include "Components/BoxComponent.h"


// Sets default values
AArenaCharacter::AArenaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArenaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArenaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AArenaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AArenaCharacter::PickShield(APickableBase* pickedShield)
{
	if (!pickedShield)
	{
		return false
	}

	if (!myShieldActor)
	{
		if (pickedShield->AttachItemTo(GetMesh(), TEXT("DualWeaponPoint")))
		{
			myShieldActor = pickedShield;
			return true;
		}
	}
	return false;
}

bool AArenaCharacter::PickWeapon(APickableWeapon* pickedWeapon)
{
	if (!pickedWeapon)
	{
		return false
	}

	if (!myWeaponActor)
	{
		if (pickedWeapon->AttachItemTo(GetMesh(), TEXT("WeaponPoint")))
		{
			myWeaponActor = pickedWeapon;
			weaponCollider = myWeaponActor->GetDamageBox();

			weaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			return true;
		}
	}
	return false;
}

