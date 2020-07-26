// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "PickableBase.h"
#include "PickableWeapon.h"
#include "Engine/World.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Components/BoxComponent.h"

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	CreateAndAttachWeapon();
}

void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAttacking)
	{
		if (weaponCollider != nullptr)
		{
			weaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
	}
	else
	{
		if (weaponCollider != nullptr)
		{
			weaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			if (!canDetectCollision)
				canDetectCollision = true;
		}
	}
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

		weaponCollider = newWeapon->GetDamageBox();
		if (weaponCollider != nullptr)
		{
			weaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			weaponCollider->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::OnWeaponOverlap);
		}
		
	}
}

void AAICharacter::TriggerAttack()
{
	Attack();
}

void AAICharacter::OnWeaponOverlap(UPrimitiveComponent* OverlapComp, AActor* Other, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other->ActorHasTag("Player") && canDetectCollision)
	{
		canDetectCollision = false;
		UE_LOG(LogTemp, Warning, TEXT("collide with player"));
	}
}

