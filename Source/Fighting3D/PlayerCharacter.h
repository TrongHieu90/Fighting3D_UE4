// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArenaCharacter.h"
#include "PlayerCharacter.generated.h"

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
};
