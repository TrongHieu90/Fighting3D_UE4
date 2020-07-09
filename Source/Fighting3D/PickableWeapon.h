// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableBase.h"
#include "PickableWeapon.generated.h"

class UBoxComponent;
class USphereComponent;
class USkeletalMeshComponent;

UCLASS()
class FIGHTING3D_API APickableWeapon : public APickableBase
{
	GENERATED_BODY()
public:
    
	APickableWeapon();

	UBoxComponent* GetDamageBox() const;

protected:
	UPROPERTY(EditAnywhere)
		UBoxComponent* damageBox;

	UPROPERTY(EditAnywhere)
		USphereComponent* mySphere;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeletalMesh;
};
