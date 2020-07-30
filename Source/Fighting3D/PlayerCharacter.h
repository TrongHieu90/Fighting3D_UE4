// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArenaCharacter.h"
#include "PickableWeapon.h"
#include "PickableBase.h"
#include "PlayerCharacter.generated.h"

class USoundCue;

UCLASS()
class FIGHTING3D_API APlayerCharacter : public AArenaCharacter
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	void MoveForward(float value);
	void MoveRight(float value);

	void Mouse_X(float value);
	void Mouse_Y(float value);

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool bCanAttack;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float Health = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
		USoundCue* footstepSCue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
		USoundCue* onHitSCue;
	
	bool AddedOverlapToWeapon;
	bool canDetectCollision;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlapComp, 
								AActor* Other,
								UPrimitiveComponent* otherComp,
								int32 otherBodyIndex,
								bool bFromSweep,
								const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnWeaponOverlap(UPrimitiveComponent* OverlapComp,
			AActor* Other,
			UPrimitiveComponent* otherComp,
			int32 otherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void PlaySound(USoundCue* soundCue);

	void TriggerAttack();
	bool ApplyDamage();
	void RestartGameState();
};
