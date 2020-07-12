// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableWeapon.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

APickableWeapon::APickableWeapon()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RooT"));
	mySphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	mySphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	skeletalMesh->AttachToComponent(mySphere, FAttachmentTransformRules::KeepRelativeTransform);

	damageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageBox"));
	damageBox->AttachToComponent(mySphere, FAttachmentTransformRules::KeepRelativeTransform);
}

UBoxComponent* APickableWeapon::GetDamageBox() const
{
	return damageBox;
}
