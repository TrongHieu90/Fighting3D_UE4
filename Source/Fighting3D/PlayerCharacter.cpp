// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Boxcomponent.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "AICharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "PlayerCharacter.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("starting from player"));
	//bUseControllerRotationYaw = false;
	bCanAttack = true;
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);

	if (playerSound)
	{
		playerSound->SetSound(footstepSCue);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
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
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Mouse_X", this, &APlayerCharacter::Mouse_X);
	PlayerInputComponent->BindAxis("Mouse_Y", this, &APlayerCharacter::Mouse_Y);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::TriggerAttack);
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
	if (!bIsAlive)
		return;
	if (!bIsAttacking)
	{
		FRotator CamRot = GetControlRotation();
		CamRot.Pitch = 0.0f;
		FVector MoveDir = CamRot.RotateVector(FVector::RightVector);

		GetCharacterMovement()->AddInputVector(MoveDir * value);
	}
}

void APlayerCharacter::Mouse_X(float value)
{
	auto Input = value * 100.0f * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(Input);
}

void APlayerCharacter::Mouse_Y(float value)
{
	auto Input = value * 100.0f * GetWorld()->GetDeltaSeconds() * -1.0f;
	AddControllerPitchInput(Input);
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* Other, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other->ActorHasTag("Shield"))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Collide with Shield"));
		APickableBase* pickedShield = Cast<APickableBase>(Other);
		PickShield(pickedShield);
	}
	if (Other->ActorHasTag("Hammer"))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Collide with Hammer"));
		APickableWeapon* pickedWeapon = Cast<APickableWeapon>(Other);
		PickWeapon(pickedWeapon);
	}
}

void APlayerCharacter::OnWeaponOverlap(UPrimitiveComponent* OverlapComp, AActor* Other, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other->ActorHasTag("Enemy"))
	{
		if (canDetectCollision)
			canDetectCollision = false;
		UE_LOG(LogTemp, Warning, TEXT("Player Collides with Enemy"));
		AAICharacter* aiChar = Cast<AAICharacter>(Other);
		bool enemyDead = aiChar->ApplyDamage();

		if (enemyDead)
		{
			FTimerHandle unusedHandle;
			GetWorldTimerManager().SetTimer(unusedHandle, this, &APlayerCharacter::RestartGameState, 3.0f, false);
		}
	}
}

void APlayerCharacter::TriggerAttack()
{
	if (!bIsAlive) return;
	if (myWeaponActor && bCanAttack)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Call attack"));
		bCanAttack = false;

		if (!AddedOverlapToWeapon)
		{
			AddedOverlapToWeapon = true;
			weaponCollider-> OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnWeaponOverlap);
		}
		canDetectCollision = true;
		Attack();
	}
}

void APlayerCharacter::PlaySound()
{
	if (playerSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("playing sound"));
		playerSound->Play();
	}
}

bool APlayerCharacter::ApplyDamage()
{
	Health -= 10.0f;

	if (Health <= 0)
	{
		bIsAlive = false;
		return true;
	}
	return false;
}

void APlayerCharacter::RestartGameState()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

