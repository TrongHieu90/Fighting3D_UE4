// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAnimNotifyState.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "PlayerCharacter.h"

void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp)
	{
		APlayerCharacter* player = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (player)
		{
			player->bCanAttack = false;
		}

	}
}

void UAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		APlayerCharacter* player = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (player)
		{
			player->bCanAttack = true;
			player->bIsAttacking = false;
		}

	}
}
