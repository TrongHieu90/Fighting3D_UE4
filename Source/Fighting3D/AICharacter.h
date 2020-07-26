// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArenaCharacter.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTING3D_API AAICharacter : public AArenaCharacter
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<APickableBase> Shield;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<APickableWeapon> Weapon;

	void CreateAndAttachWeapon();

	UFUNCTION(BlueprintCallable)
	void TriggerAttack();

	UFUNCTION()
		virtual void OnWeaponOverlap(UPrimitiveComponent* OverlapComp,
			AActor* Other,
			UPrimitiveComponent* otherComp,
			int32 otherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	bool canDetectCollision;
	bool disableAttack;
};
