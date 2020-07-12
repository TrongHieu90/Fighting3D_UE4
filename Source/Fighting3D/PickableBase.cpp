// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableBase.h"

// Sets default values
APickableBase::APickableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APickableBase::AttachItemTo(USkeletalMeshComponent* meshRoot, FName socket)
{
	if (isUsed)
		return false;
	AttachToComponent(meshRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale, socket);
	SetActorRelativeLocation(FVector::ZeroVector);
	SetActorRelativeRotation(FRotator::ZeroRotator);

	isUsed = true;

	return isUsed;
}

